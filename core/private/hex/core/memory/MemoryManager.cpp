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

            auto result(iter->second);

            in_iter++;

            return result;
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
#ifdef HEX_MEMORY_DEBUG // MEMORY-DEBUG
            void*                       address(iter == end_iter ? nullptr : iter->first);
#endif // MEMORY-DEBUG
            ReferenceBlock*             referenceBlock_ptr(getNextReferenceBlock(iter));
            while (referenceBlock_ptr)
            {
#ifdef HEX_DEBUG // DEBUG
                    assert(referenceBlock_ptr && "MemoryManager::deleteObjects: reference block is null");
#endif // DEBUG
                ReferenceBlock& block(*referenceBlock_ptr);

                hexMutex& blockMutex(*(block.mMutex));
                hexLock   blockLock(blockMutex, true);
                blockLock.try_lock();

                // Get any available user for deletion logic
                hexVector<IReferenceUser*>& users(block.mUsers);
                usersCount = users.size();

#ifdef HEX_MEMORY_DEBUG // MEMORY-DEBUG
                std::string logMsg("MemoryManager::deleteObjects: address=");
                logMsg += std::to_string( reinterpret_cast<size_t>(address) );
                logMsg += "; counter=";
                logMsg += std::to_string(referenceBlock_ptr->mCounter);
                logMsg += "; users.count=";
                logMsg += std::to_string(usersCount);
                hexLog::Debug(logMsg.c_str());
#endif // MEMORY-DEBUG

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
#ifdef HEX_MEMORY_DEBUG // MEMORY-DEBUG
                address = referenceBlock_ptr ? iter->first : nullptr;
#endif // MEMORY-DEBUG
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

            bool            isEmptySlotFound(false);
            const size_t    usersCount(block->mUsers.size());
            for (size_t i = 0; i < usersCount; i++)
            {
                if (!block->mUsers[i])
                {
                    isEmptySlotFound = true;
                    block->mUsers[i] = pUser;
                    break;
                }
            }

            if (!isEmptySlotFound)
                block->mUsers.push_back(pUser);

#ifdef HEX_MEMORY_DEBUG // MEMORY-DEBUG
            std::string logMsg("MemoryManager::addReferenceUser: address=");
            logMsg += std::to_string(reinterpret_cast<size_t>(pAddress));
            logMsg += "; counter=";
            logMsg += std::to_string(block->mCounter);
            logMsg += "; previous mReferencesBlocks.size=";
            logMsg += std::to_string(mReferencesBlocks.size());
            hexLog::Debug(logMsg.c_str());
#endif // MEMORY-DEBUG

            block->mMutex->unlock();
        }

        void MemoryManager::removeReferenceUser(void* const pAddress, IReferenceUser* pUser) HEX_NOEXCEPT
        {
            ReferenceBlock* const block(getReferenceBlock(pAddress, false));
            if (!block)
                return;

            IReferenceUser* user(nullptr);
            const size_t    usersCount(block->mUsers.size());
            for (size_t i = 0; i < usersCount; i++)
            {
                user = block->mUsers[i];
                if (user == pUser)
                {
                    block->mUsers[i] = nullptr;
                    break;
                }
            }

            block->mCounter--;

#ifdef HEX_MEMORY_DEBUG // MEMORY-DEBUG
            std::string logMsg("MemoryManager::removeReferenceUser: address=");
            logMsg += std::to_string(reinterpret_cast<size_t>(pAddress));
            logMsg += "; counter=";
            logMsg += std::to_string(block->mCounter);
            logMsg += "; previous mReferencesBlocks.size=";
            logMsg += std::to_string(mReferencesBlocks.size());
            hexLog::Debug(logMsg.c_str());
#endif // MEMORY-DEBUG

            if (block->mCounter < 1)
            {
                pUser->onDeleteObject();

                hexLock blocksLock(mReferencesCountersMutex);
                mReferencesBlocks.erase(pAddress);
                blocksLock.unlock();

                delete block->mMutex; // Trigger unlock() through destructor
                delete block;

#ifdef HEX_MEMORY_DEBUG // MEMORY-DEBUG
            std::string logMsg("MemoryManager::removeReferenceUser: address=");
            logMsg += std::to_string(reinterpret_cast<size_t>(pAddress));
            logMsg += "; block deleted. new mReferencesBlocks.size=";
            logMsg += std::to_string(mReferencesBlocks.size());
            hexLog::Debug(logMsg.c_str());
#endif // MEMORY-DEBUG

                return;
            }

            block->mMutex->unlock();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
