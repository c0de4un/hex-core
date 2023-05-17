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
#ifndef HEX_ECS_EVENT_HPP
    #include <hex/core/ecs/Event.hpp>
#endif /// !HEX_ECS_EVENT_HPP

// Include hex::core::EventsManager
#ifndef HEX_ECS_BASE_MANAGER_HPP
    #include <hex/core/ecs/EventsManager.hpp>
#endif /// !HEX_ECS_BASE_MANAGER_HPP

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Event
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace ecs
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTORS & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        Event::Event(const ecs_TypeID typeId)
            :
            mTypeID(typeId),
            mID(EventsManager::generateEventID(typeId)),
            mHandled(false)
        {
        }

        Event::~Event() noexcept
        {
            EventsManager::releaseEventID(mTypeID, mID);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // OVERRIDE.IEvent
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        ecs_TypeID Event::getTypeID() const noexcept
        {
            return mTypeID;
        }

        ecs_ObjectID Event::getID() const noexcept
        {
            return mID;
        }

        bool Event::isHandled() const noexcept
        {
            const bool handled(mHandled);

            return handled;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
