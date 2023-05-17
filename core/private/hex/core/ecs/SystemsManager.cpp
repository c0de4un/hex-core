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
#ifndef HEX_ECS_SYSTEMS_MANAGER_HPP
    #include <hex/core/ecs/SystemsManager.hpp>
#endif /// !HEX_ECS_SYSTEMS_MANAGER_HPP

#ifdef HEX_LOGGING // LOG

    // Include hex::core::debug
    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif /// LOG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// SystemsManager
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace ecs
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // FIELDS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        SystemsManager* SystemsManager::mInstance(nullptr);

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        SystemsManager::SystemsManager()
            :
            BaseManager()
        {
        }

        SystemsManager::~SystemsManager() noexcept = default;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void SystemsManager::Initialize()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("SystemsManager::Initialize");
#endif // LOG

#ifdef HEX_DEBUG // DEBUG
            assert(!mInstance && "SystemsManager::Initialize: already initialized");
#endif // DEBUG

            if (mInstance)
                return;

            mInstance = new SystemsManager();
        }

        void SystemsManager::Terminate() noexcept
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("SystemsManager::Terminate");
#endif // LOG

#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "SystemsManager::Terminate: already terminated");
#endif // DEBUG

            delete mInstance;
            mInstance = nullptr;
        }

        ecs_ObjectID SystemsManager::generateSystemID(const ecs_TypeID typeID)
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "SystemsManager::generateSystemID: not initialized");
#endif // DEBUG

            if (!mInstance)
                return ECS_INVALID_OBJECT_ID;

            return mInstance->generateID(typeID);
        }

        void SystemsManager::releaseSystemID(const ecs_TypeID typeID, const ecs_ObjectID id) noexcept
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "SystemsManager::releaseSystemID: not initialized");
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
