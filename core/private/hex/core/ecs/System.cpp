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
#ifndef HEX_ECS_SYSTEM_HPP
    #include <hex/core/ecs/System.hpp>
#endif /// !HEX_ECS_SYSTEM_HPP

// Include hex::ecs::SystemsManager
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
// System
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace ecs
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        System::System(const ecs_TypeID in_type)
            :
            mTypeID(in_type),
            mID(ecs_Systems::generateSystemID(in_type)),
            mState(System::STATE_NONE)
        {
        }

        System::~System() noexcept = default;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // GETTERS & SETTERS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void System::setState(const System::state_t state) noexcept
        {
            mState = state;
        }

        bool System::isStarted() const noexcept
        {
            const System::state_t state(mState);

            return state > System::STATE_NONE;
        }

        bool System::isPaused() const noexcept
        {
            const System::state_t state(mState);

            return state > System::STATE_RUNNING && state < System::STATE_PAUSING;
        }

        ecs_TypeID System::getTypeID() const noexcept
        {
            return mTypeID;
        }

        ecs_ObjectID System::getID() const noexcept
        {
            return mID;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS.System
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool System::onStart()
        {
            setState(System::STATE_RUNNING);

            return true;
        }

        bool System::onResume()
        {
            setState(System::STATE_RUNNING);

            return true;
        }

        void System::onPause()
        {
            setState(System::STATE_PAUSED);
        }

        void System::onStop()
        {
            setState(System::STATE_NONE);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS.ISystem
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool System::Start()
        {
#ifdef HEX_LOGGING // LOG
            std::string logMsg("System#");
            logMsg += std::to_string(mTypeID);
            logMsg += ":";
            logMsg += mID;
            logMsg += "::Start";
            hexLog::Debug(logMsg.c_str());
#endif // LOG

            if (isStarted()) {
                if (isPaused())
                {
                    setState(System::STATE_STARTING);

                    return onResume();
                }

                return true;
            }

            setState(System::STATE_STARTING);

            return onStart();
        }

        void System::Pause()
        {
#ifdef HEX_LOGGING // LOG
            std::string logMsg("System#");
            logMsg += std::to_string(mTypeID);
            logMsg += ":";
            logMsg += mID;
            logMsg += "::Pause";
            hexLog::Debug(logMsg.c_str());
#endif // LOG

            if (!isStarted() || isPaused())
                return;

            setState(System::STATE_PAUSING);

            onPause();
        }

        void System::Stop() noexcept
        {
#ifdef HEX_LOGGING // LOG
            std::string logMsg("System#");
            logMsg += std::to_string(mTypeID);
            logMsg += ":";
            logMsg += mID;
            logMsg += "::Stop";
            hexLog::Debug(logMsg.c_str());
#endif // LOG

            if (!isStarted())
                return;

            setState(System::STATE_STOPPING);

            onStop();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
