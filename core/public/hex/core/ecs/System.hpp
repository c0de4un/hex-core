/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#ifndef HEX_ECS_SYSTEM_HPP
#define HEX_ECS_SYSTEM_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Include hex::ecs::ISystem
#ifndef HEX_ECS_I_SYSTEM_HXX
    #include <hex/core/ecs/ISystem.hxx>
#endif /// !HEX_ECS_I_SYSTEM_HXX

// Include hex::core::mutex
#ifndef HEX_CORE_CFG_MUTEX_HPP
    #include <hex/core/cfg/hex_mutex.hpp>
#endif /// !HEX_CORE_CFG_MUTEX_HPP

// Include hex::core::atomic
#ifndef HEX_CORE_CFG_ATOMIC_HPP
    #include <hex/core/cfg/hex_atomic.hpp>
#endif /// !HEX_CORE_CFG_ATOMIC_HPP

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// System
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace ecs
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        HEX_API class System : public ISystem
        {

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // META
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            HEX_CLASS

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        protected:

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // ALIASES
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            using state_t = unsigned char;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // CONSTANTS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            static constexpr const state_t STATE_NONE     = 0;
            static constexpr const state_t STATE_STARTING = 1;
            static constexpr const state_t STATE_RUNNING  = 2;
            static constexpr const state_t STATE_PAUSING  = 3;
            static constexpr const state_t STATE_PAUSED   = 4;
            static constexpr const state_t STATE_STOPPING = 5;

            const ecs_TypeID   mTypeID;
            const ecs_ObjectID mID;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // FIELDS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            hex_atomic<state_t> mState;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // CONSTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            explicit System(const ecs_TypeID in_type);

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // GETTERS & SETTERS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            void setState(const state_t state) noexcept;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // METHODS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            virtual bool onStart();
            virtual bool onResume();
            virtual void onPause();
            virtual void onStop();

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // DELETED
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            System(const System&)            = delete;
            System& operator=(const System&) = delete;
            System(System&&)                 = delete;
            System& operator=(System&&)      = delete;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        public:

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // DESTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            virtual ~System() noexcept;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // OVERRIDE.ISystem
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            virtual ecs_TypeID getTypeID() const noexcept final;
            virtual ecs_ObjectID getID() const noexcept   final;

            virtual bool isStarted() const noexcept final;
            virtual bool isPaused() const noexcept  final;

            virtual bool Start()         final;
            virtual void Pause()         final;
            virtual void Stop() noexcept final;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        };

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif /// !HEX_ECS_SYSTEM_HPP
