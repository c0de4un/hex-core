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
#ifndef HEX_ECS_ENTITIES_MANAGER_HPP
    #include <hex/core/ecs/EntitiesManager.hpp>
#endif /// !HEX_ECS_ENTITIES_MANAGER_HPP

#ifdef HEX_LOGGING // LOG

    // Include hex::core::debug
    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif /// LOG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// EntitiesManger
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace ecs
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // FIELDS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        EntitiesManager* EntitiesManager::mInstance(nullptr);

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        EntitiesManager::EntitiesManager()
            :
            BaseManager()
        {
        }

        EntitiesManager::~EntitiesManager() noexcept = default;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void EntitiesManager::Initialize()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("EntitiesManager::Initialize");
#endif // LOG

#ifdef HEX_DEBUG // DEBUG
            assert(!mInstance && "EntitiesManager::Initialize: already initialized");
#endif // DEBUG

            if (mInstance)
                return;

            mInstance = new EntitiesManager();
        }

        void EntitiesManager::Terminate() noexcept
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("EntitiesManager::Terminate");
#endif // LOG

#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "EntitiesManager::Initialize: already terminated");
#endif // DEBUG

            delete mInstance;
            mInstance = nullptr;
        }

        ecs_ObjectID EntitiesManager::generateEntityID(const ecs_TypeID typeID)
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "EntitiesManager::generateEntityID: not initialized");
#endif // DEBUG

            if (!mInstance)
                return ECS_INVALID_OBJECT_ID;

            return mInstance->generateID(typeID);
        }

        void EntitiesManager::releaseEntityID(const ecs_TypeID typeID, const ecs_ObjectID id) noexcept
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "EntitiesManager::releaseEntityID: not initialized");
#endif // DEBUG

            if (!mInstance)
                return;

            try
            {
                mInstance->releaseID(typeID, id);
            }
            catch (...)
            {
                // void
            }
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
