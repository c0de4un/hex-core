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
#ifndef HEX_CORE_ASSETS_SYSTEM_HPP
    #include <hex/core/assets/AssetsSystem.hpp>
#endif /// !HEX_CORE_ASSETS_SYSTEM_HPP

// Include hex::core::Material
#ifndef HEX_CORE_MATERIAL_HPP
    #include <hex/core/assets/Material.hpp>
#endif /// !HEX_CORE_MATERIAL_HPP

#ifdef HEX_LOGGING // LOG

    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif // LOG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// AssetsSystem
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace core
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // FIELDS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        hexMutex                AssetsSystem::mInstanceMutex;
        hexShared<AssetsSystem> AssetsSystem::mpInstance(nullptr);

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        AssetsSystem::AssetsSystem()
            :
            System(static_cast<ecs_TypeID>(hexESystems::ASSETS))
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("AssetsSystem::constructor");
#endif // LOG
        }

        AssetsSystem::~AssetsSystem() noexcept
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("AssetsSystem::destructor");
#endif // LOG
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // PUBLIC: GETTERS & SETTERS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        hexShared<AssetsSystem> AssetsSystem::getInstance()
        {
            hexLock lock(mInstanceMutex);

            return mpInstance;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // PROTECTED: GETTERS & SETTERS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void AssetsSystem::setInstance(AssetsSystem* const pInstance)
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("AssetsSystem::setInstance");
#endif // LOG

            hexLock lock(mInstanceMutex);

#ifdef HEX_DEBUG // DEBUG
            assert(!mpInstance.get() && "AssetsSystem::setInstance: already set");
#endif // DEBUG

            if (!mpInstance.get())
                mpInstance.reset(pInstance);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // PUBLIC: METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void AssetsSystem::Terminate() noexcept
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("AssetsSystem::Terminate");
#endif // LOG

            hexLock lock(mInstanceMutex);

#ifdef HEX_DEBUG // DEBUG
            assert(mpInstance.get() && "AssetsSystem::Terminate: already Terminated");
#endif // DEBUG

            mpInstance.reset(nullptr);
        }

        hexShared<hexMaterial> AssetsSystem::createMaterial(const hexString name)
        {
            return hexShared<Material>(new hexMaterial(name));
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
