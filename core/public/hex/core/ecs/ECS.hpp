/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#ifndef HEX_ECS_HPP
#define HEX_ECS_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Include hex::core::api
#ifndef HEX_CORE_CFG_API_HPP
    #include <hex/core/cfg/hex_api.hpp>
#endif /// !HEX_CORE_CFG_API_HPP

// Compiler-Only

// Include hex::ecs::Component
#ifndef HEX_ECS_COMPONENT_HPP
    #include <hex/core/ecs/Component.hpp>
#endif /// !HEX_ECS_COMPONENT_HPP

// Include hex::ecs::ComponentsManager
#ifndef HEX_ECS_COMPONENTS_MANAGER_HPP
    #include <hex/core/ecs/ComponentsManager.hpp>
#endif /// !HEX_ECS_COMPONENTS_MANAGER_HPP

// Include hex::ecs::System
#ifndef HEX_ECS_SYSTEM_HPP
    #include <hex/core/ecs/System.hpp>
#endif /// !HEX_ECS_SYSTEM_HPP

// Include hex::ecs::SystemsManager
#ifndef HEX_ECS_SYSTEMS_MANAGER_HPP
    #include <hex/core/ecs/SystemsManager.hpp>
#endif /// !HEX_ECS_SYSTEMS_MANAGER_HPP

// Include hex::ecs::EntitiesManager
#ifndef HEX_ECS_ENTITIES_MANAGER_HPP
    #include <hex/core/ecs/EntitiesManager.hpp>
#endif /// !HEX_ECS_ENTITIES_MANAGER_HPP

// Include hex::ecs::Entity
#ifndef HEX_ECS_ENTITY_HPP
    #include <hex/core/ecs/Entity.hpp>
#endif /// !HEX_ECS_ENTITY_HPP

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// TYPES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace ecs
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // ECS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        HEX_API class ECS final
        {

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // META
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            HEX_CLASS

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        private:

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // CONSTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            explicit ECS() noexcept;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // DELETED
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            ECS(const ECS&)            = delete;
            ECS& operator=(const ECS&) = delete;
            ECS(ECS&&)                 = delete;
            ECS& operator=(ECS&&)      = delete;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        public:

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // DESTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            ~ECS() noexcept;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // METHODS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            static void Initialize();
            static void Terminate() noexcept;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        };

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

using hexECS = hex::ecs::ECS;

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif /// !HEX_ECS_HPP
