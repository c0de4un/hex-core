/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#ifndef HEX_ECS_EVENTS_MANAGER_HPP
#define HEX_ECS_EVENTS_MANAGER_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Include hex::ecs::BaseManager
#ifndef HEX_ECS_BASE_MANAGER_HPP
    #include <hex/core/ecs/BaseManager.hpp>
#endif /// !HEX_ECS_BASE_MANAGER_HPP

// Include hex::memory
#ifndef HEX_CORE_CFG_MEMORY_HPP
    #include <hex/core/cfg/hex_memory.hpp>
#endif /// !HEX_CORE_CFG_MEMORY_HPP

// Include hex::map
#ifndef HEX_CORE_CFG_MAP_HPP
    #include <hex/core/cfg/hex_map.hpp>
#endif /// !HEX_CORE_CFG_MAP_HPP

// Include hex::vector
#ifndef HEX_CORE_CFG_VECTOR_HPP
    #include <hex/core/cfg/hex_vector.hpp>
#endif /// !HEX_CORE_CFG_VECTOR_HPP

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// FORWARD-DECLARATIONS
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Forward-Declare hex::ecs::EventsCollection
#ifndef HEX_ECS_EVENTS_COLLECTION_DECL
    #define HEX_ECS_EVENTS_COLLECTION_DECL
    namespace hex { namespace ecs { struct EventsCollection; } }
#endif /// !HEX_ECS_EVENTS_COLLECTION_DECL

    // Forward-Declare hex::ecs::EventHandlersCollection
#ifndef HEX_ECS_EVENT_HANDLERS_COLLECTION_DECL
    #define HEX_ECS_EVENT_HANDLERS_COLLECTION_DECL
    namespace hex { namespace ecs { struct EventHandlersCollection; } }
#endif /// !HEX_ECS_EVENT_HANDLERS_COLLECTION_DECL

// Forward-Declare hex::ecs::IEvent
#ifndef HEX_ECS_I_EVENT_DECL
    #define HEX_ECS_I_EVENT_DECL
    namespace hex { namespace ecs { class IEvent; } }
    using ecsIEvent = hex::ecs::IEvent;
#endif /// !HEX_ECS_I_EVENT_DECL

// Forward-Declare hex::ecs::IEventHandler
#ifndef HEX_ECS_I_EVENT_HANDLER_DECL
    #define HEX_ECS_I_EVENT_HANDLER_DECL
    namespace hex { namespace ecs { class IEventHandler; } }
    using ecsIEventHandler = hex::ecs::IEventHandler;
#endif /// !HEX_ECS_I_EVENT_HANDLER_DECL

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// EventsManager
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace ecs
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        HEX_API class EventsManager final : public BaseManager
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
            // ALIASES
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            using events_ptr  = hexShared<EventsCollection>;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // FIELDS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            static EventsManager* mInstance;

            hexMutex                       mEventsMutex;
            hexMap<ecs_TypeID, events_ptr> mEventsCollections;

            hexMutex                                               mHandlersMutex;
            hexMap<ecs_TypeID, hexShared<EventHandlersCollection>> mHandlersCollections;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // CONSTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            explicit EventsManager();

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // GETTERS & SETTERS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            inline events_ptr getEventsCollection(const ecs_TypeID typeId, const bool create);
            inline hexShared<EventHandlersCollection> getHandlersCollection(const ecs_TypeID typeId, const bool create);
            inline hexShared<ecsIEventHandler> getNextHandler(size_t i, EventHandlersCollection& handlers);

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // DELETED
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            EventsManager(const EventsManager&)            = delete;
            EventsManager& operator=(const EventsManager&) = delete;
            EventsManager(EventsManager&&)                 = delete;
            EventsManager& operator=(EventsManager&&)      = delete;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        public:

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // DESTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            virtual ~EventsManager() noexcept;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // METHODS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            static void Initialize();
            static void Terminate() noexcept;

            static ecs_ObjectID generateEventID(const ecs_TypeID typeID);
            static void releaseEventID(const ecs_TypeID typeID, const ecs_ObjectID id) noexcept;

            void registerHandler(const ecs_TypeID typeId, hexShared<ecsIEventHandler> pHandler);
            void unregisterHandler(const ecs_TypeID typeId, ecsIEventHandler* const pHandler) noexcept;

            void queueEvent(hexShared<ecsIEvent> pEvent);
            void sendEvent(hexShared<ecsIEvent> pEvent);

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        };

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

using ecs_Events = hex::ecs::EventsManager;

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif /// !HEX_ECS_EVENTS_MANAGER_HPP
