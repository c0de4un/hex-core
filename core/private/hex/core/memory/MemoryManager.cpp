/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// HEADER
#ifndef HEX_CORE_MEMORY_MANAGER_HPP
    #include <hex/core/memory/MemoryManager.hpp>
#endif /// !HEX_CORE_MEMORY_MANAGER_HPP

// Include hex::core::IReferenceUser
#ifndef HEX_CORE_I_REFERENCE_USER_HXX
    #include <hex/core/memory/IReferenceUser.hxx>
#endif /// !HEX_CORE_I_REFERENCE_USER_HXX

#ifdef HEX_LOGGING /// DEBUG

    // Include hex::core::debug
    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif /// DEBUG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// MemoryManager
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace core
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // FIELDS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        hexMutex       MemoryManager::mInstanceMutex;
        MemoryManager* MemoryManager::mInstance(nullptr);

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        MemoryManager::MemoryManager()
            :
            mReferencesCountersMutex(),
            mReferencesBlocks()
        {
#ifdef HEX_LOGGING // DEBUG
            hexLog::Debug("MemoryManager::constructor");
#endif // DEBUG
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        MemoryManager::~MemoryManager() noexcept
        {
#ifdef HEX_LOGGING // DEBUG
            hexLog::Debug("MemoryManager::destructor");
#endif // DEBUG

            // To prevent dead-locks when triggering smart-pointers and objects destructors
            mInstance = nullptr;

            // Delete objects
            deleteObjects();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // GETTERS & SETTERS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        MemoryManager* const MemoryManager::getInstance() noexcept
        {
            return mInstance;
        }

        size_t MemoryManager::getReferenceCount(void* pAddress) const HEX_NOEXCEPT
        {
            hexLock lock(mReferencesCountersMutex, true);

            return mReferencesBlocks.size();
        }

        ReferenceBlock* MemoryManager::getNextReferenceBlock(hexMap<void*, ReferenceBlock*>::iterator& in_iter) noexcept
        {
            hexLock    lock(mReferencesCountersMutex, true);
            const auto end_iter(mReferencesBlocks.cend());
            auto       iter(mReferencesBlocks.begin());
            bool       hasNext(false);

            lock.try_lock(); // Doesn't matter, if not locked

            while (iter != end_iter)
            {
                if (iter == in_iter)
                {
                    hasNext = true;
                    break;
                }

                iter++;
            }

            if (!hasNext)
                return nullptr;

            iter++;

            return iter->second;
        }

        ReferenceBlock* MemoryManager::getReferenceBlock(void* pAddress, const bool allocate)
        {
            hexLock lock(mReferencesCountersMutex);

            auto pos(mReferencesBlocks.find(pAddress));
            if (pos == mReferencesBlocks.end())
            {
                if (!allocate)
                    return nullptr;

                ReferenceBlock* block(new ReferenceBlock{
                    0,                                                                  // mCounter
                    new hexMutex(),                                                     // mMutex
                    std::move<hexVector<IReferenceUser*>>(hexVector<IReferenceUser*>()) // mUsers
                });

                mReferencesBlocks.insert(
                    std::pair<void*, ReferenceBlock*>(pAddress, block)
                );

                block->mMutex->lock(); // To prevent deletion by concurrent
                return block;
            }

            return pos->second;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void MemoryManager::deleteObjects() noexcept
        {
            hexLock lock(mReferencesCountersMutex, true);
            try
            {
                lock.lock();
            }
            catch (...)
            {
                // void
            }

            size_t                      i(0);
            size_t                      usersCount(0);
            IReferenceUser*             user(nullptr);
            const auto                  end_iter(mReferencesBlocks.cend());
            auto                        iter(mReferencesBlocks.begin());
            ReferenceBlock*             referenceBlock_ptr(getNextReferenceBlock(iter));
            while (referenceBlock_ptr)
            {
#ifdef HEX_DEBUG // DEBUG
                    assert(referenceBlock_ptr && "MemoryManager::deleteObjects: reference block is null");
                    assert(referenceBlock_ptr->mCounter > 0 && "MemoryManager::deleteObjects: bad reference block deletion logic, counter is 0");
#endif // DEBUG
                ReferenceBlock& block(*referenceBlock_ptr);

                hexMutex& blockMutex(*(block.mMutex));
                hexLock   blockLock(blockMutex, true);
                blockLock.try_lock();

                // Get any available user for deletion logic
                hexVector<IReferenceUser*>& users(block.mUsers);
                usersCount = users.size();

#ifdef HEX_DEBUG // DEBUG
                assert(usersCount > 0 && "MemoryManager::deleteObjects: bad reference block deletion logic, size is 0");
#endif // DEBUG

                for (i = 0; i < usersCount; i++)
                {
                    user = users[i];
                    if (user)
                        break;
                }

#ifdef HEX_DEBUG // DEBUG
                assert(static_cast<bool>(user) && "MemoryManager::deleteObjects: bad reference block deletion logic, all users pointers are nullptr");
#endif // DEBUG

                // Delete
                user->onDeleteObject();
                block.mCounter = 0;
                block.mUsers.clear(); // Trigger all smart-points destructors

                referenceBlock_ptr = getNextReferenceBlock(iter);
            }
        }

        void MemoryManager::Initialize()
        {
#ifdef HEX_LOGGING // LOGGING
            hexLog::Info("MemoryManager::Initialize");
#endif // LOGGING

            hexLock lock(mInstanceMutex);

#ifdef HEX_DEBUG // DEBUG
            assert(!mInstance && "MemoryManager::Initialize: already initialized");
#endif // DEBUG

            if (mInstance)
                return;

            mInstance = new MemoryManager();
        }

        void MemoryManager::Terminate() noexcept
        {
#ifdef HEX_LOGGING // LOGGING
            hexLog::Info("MemoryManager::Terminate");
#endif // LOGGING

            hexLock lock(mInstanceMutex);

            delete mInstance;
            mInstance = nullptr;
        }

        void MemoryManager::addReferenceUser(void* const pAddress, IReferenceUser* pUser) HEX_NOEXCEPT
        {
            ReferenceBlock* const block(getReferenceBlock(pAddress, true));
            block->mCounter++;
            block->mUsers.push_back(pUser);

            block->mMutex->unlock();
        }

        void MemoryManager::removeReferenceUser(void* const pAddress, IReferenceUser* pUser) HEX_NOEXCEPT
        {
            ReferenceBlock* const block(getReferenceBlock(pAddress, false));
            if (!block)
                return;

            block->mCounter--;
            if (block->mCounter < 1)
            {
                pUser->onDeleteObject();

                hexLock blocksLock(mReferencesCountersMutex);
                mReferencesBlocks.erase(pAddress);
                blocksLock.unlock();

                delete block->mMutex; // Trigger unlock() through destructor
                delete block;
                return;
            }

            block->mMutex->unlock();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
