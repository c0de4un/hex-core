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
#ifndef HEX_ECS_BASE_MANAGER_HPP
    #include <hex/core/ecs/BaseManager.hpp>
#endif /// !HEX_ECS_BASE_MANAGER_HPP

#ifdef HEX_LOGGING // LOG

    // Include hex::core::debug
    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif /// LOG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// BaseManager
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace ecs
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        BaseManager::BaseManager()
            :
            mIDStorageMutex(),
            mIDStorages()
        {
        }

        BaseManager::~BaseManager() noexcept
        {
            this->deleteIDStorages();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // GETTERS & SETTERS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        BaseManager::comp_storage_t* BaseManager::getIDStorageByTypeID(const ecs_TypeID typeID)
        {
            hexLock lock(mIDStorageMutex);

            BaseManager::comp_storage_t* storage(nullptr);

            auto pos(mIDStorages.find(typeID));
            if (pos == mIDStorages.end())
            {
                storage = new BaseManager::comp_storage_t();

                mIDStorages.insert(
                    std::pair<ecs_TypeID, BaseManager::comp_storage_t*>(
                        typeID,
                        storage
                    )
                );
            }
            else
                storage = pos->second;

            return storage;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        ecs_ObjectID BaseManager::generateID(const ecs_TypeID typeID)
        {
            BaseManager::comp_storage_t* const idStorage(
                getIDStorageByTypeID(typeID)
            );

            return idStorage->reserve();
        }

        void BaseManager::releaseID(const ecs_TypeID typeID, const ecs_ObjectID id)
        {
            BaseManager::comp_storage_t* const idStorage(
                getIDStorageByTypeID(typeID)
            );

            idStorage->put(id);
        }

        void BaseManager::deleteIDStorages() noexcept
        {
            hexLock lock(mIDStorageMutex, true);
            try { lock.lock(); }
            catch (...) { /** void */ }

            auto       iter(mIDStorages.begin());
            const auto end_iter(mIDStorages.cend());
            while (iter != end_iter)
            {
                delete iter->second;
            }
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
