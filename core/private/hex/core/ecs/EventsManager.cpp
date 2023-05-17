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
#ifndef HEX_ECS_EVENTS_MANAGER_HPP
    #include <hex/core/ecs/EventsManager.hpp>
#endif /// !HEX_ECS_EVENTS_MANAGER_HPP

// Include hex::ecs::IEvent
#ifndef HEX_ECS_I_EVENT_HXX
    #include <hex/core/ecs/IEvent.hxx>
#endif /// !HEX_ECS_I_EVENT_HXX

// Include hex::ecs::IEventHandler
#ifndef HEX_ECS_I_EVENT_HANDLER_HXX
    #include <hex/core/ecs/IEventHandler.hxx>
#endif /// !HEX_ECS_I_EVENT_HANDLER_HXX

// Include hex::ecs::EventsCollection
#ifndef HEX_ECS_EVENTS_COLLECTION_HPP
    #include <hex/core/ecs/EventsCollection.hpp>
#endif /// !HEX_ECS_EVENTS_COLLECTION_HPP

// Include hex::ecs::EventHandlersCollection
#ifndef HEX_ECS_EVENT_HANDLERS_COLLECTION_HPP
    #include <hex/core/ecs/EventHandlersCollection.hpp>
#endif /// !HEX_ECS_EVENT_HANDLERS_COLLECTION_HPP

#ifdef HEX_LOGGING // LOG

    // Include hex::core::debug
    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif /// LOG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// EventsManager
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace ecs
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // FIELDS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        EventsManager* EventsManager::mInstance(nullptr);

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        EventsManager::EventsManager()
            :
            BaseManager(),
            mEventsMutex(),
            mEventsCollections(),
            mHandlersMutex(),
            mHandlersCollections()
        {
        }

        EventsManager::~EventsManager() noexcept = default;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // PUBLIC: METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void EventsManager::Initialize()
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("EventsManager::Initialize");
#endif // LOG

#ifdef HEX_DEBUG // DEBUG
            assert(!mInstance && "EventsManager::Initialize: already initialized");
#endif // DEBUG

            if (mInstance)
                return;

            mInstance = new EventsManager();
        }

        void EventsManager::Terminate() noexcept
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("EventsManager::Terminate");
#endif // LOG

#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "EventsManager::Terminate: already terminated");
#endif // DEBUG

            delete mInstance;
            mInstance = nullptr;
        }

        ecs_ObjectID EventsManager::generateEventID(const ecs_TypeID typeID)
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "EventsManager::generateEventID: not initialized");
#endif // DEBUG

            if (!mInstance)
                return ECS_INVALID_OBJECT_ID;

            return mInstance->generateID(typeID);
        }

        void EventsManager::releaseEventID(const ecs_TypeID typeID, const ecs_ObjectID id) noexcept
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "EventsManager::releaseEventID: not initialized");
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

        void EventsManager::registerHandler(const ecs_TypeID typeId, hexShared<ecsIEventHandler> pHandler)
        {
            auto handlers(getHandlersCollection(typeId, true));

            auto& handlers_ref(handlers->mHandlers);
            hexLock lock(handlers->mMutex);

            const size_t handlersCount(handlers_ref.size());

#ifdef HEX_DEBUG // DEBUG
            bool _isDuplicated(false);
            for (size_t i = 0; i < handlersCount; i++)
            {
                auto& handler(handlers_ref.at(i));
                if (handler.get() == pHandler.get())
                {
                    _isDuplicated = true;
                    break;
                }
            }

            assert(!_isDuplicated && "EventsManager::registerHandler: duplication, handler already been registered. Fix logic");
#endif // DEBUG

            for (size_t i = 0; i < handlersCount; i++)
            {
                auto& handler(handlers_ref.at(i));
                if (!handler.get())
                {
                    handler.reset(pHandler.get());
                    return;
                }
            }

            handlers_ref.push_front(pHandler);
        }

        void EventsManager::unregisterHandler(const ecs_TypeID typeId, ecsIEventHandler* const pHandler) noexcept
        {
            auto handlers(getHandlersCollection(typeId, false));
            if (!handlers.get())
                return;

            auto& handlers_ref(handlers->mHandlers);

            hexLock lock(handlers->mMutex);

            const size_t handlersCount(handlers_ref.size());
            for (size_t i = 0; i < handlersCount; i++)
            {
                auto& handler(handlers_ref.at(i));
                if (handler == pHandler)
                {
                    handler.reset();
                    return;
                }
            }
        }

        void EventsManager::queueEvent(hexShared<ecsIEvent> pEvent)
        {
            auto eventsCollection_ptr(getEventsCollection(pEvent->getTypeID(), true));

            hexLock lock(eventsCollection_ptr->mMutex);
            
            auto& queue_ref(eventsCollection_ptr->mQueue);
            const size_t handlerCount(queue_ref.size());
            for (size_t i = 0; i < handlerCount; i++)
            {
                auto& slot(queue_ref.at(i));
                if (!slot.get())
                {
                    slot.reset(pEvent.get());
                    return;
                }
            }

            queue_ref.push_back(pEvent); // Copy
        }

        void EventsManager::sendEvent(hexShared<ecsIEvent> pEvent)
        {
            auto  handlers(getHandlersCollection(pEvent->getTypeID(), false));
            auto& handlers_ref( *(handlers.get()) );
            size_t handlerIndex(1);
            hexShared<ecsIEventHandler> handler(getNextHandler(0, handlers_ref));
            while (handler.get())
            {
                if (handler->handleEvent(pEvent))
                {
                    pEvent.get()->setHandled(true);
                    return;
                }

                handlerIndex++;
                handler = getNextHandler(handlerIndex, handlers_ref).get();
            }
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // PRIVATE: GETTERS & SETTERS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        EventsManager::events_ptr EventsManager::getEventsCollection(const ecs_TypeID typeId, const bool create)
        {
            hexLock lock(mEventsMutex);

            auto pos(mEventsCollections.find(typeId));
            if (pos != mEventsCollections.cend())
                return pos->second;

            if (!create)
                return hexShared<EventsCollection>(nullptr);

            // 1 Move operation, and 1 Copy
            hexShared<EventsCollection> eventsCollection(new EventsCollection());

            mEventsCollections.insert(std::pair<ecs_TypeID, hexShared<EventsCollection>>(
                typeId,
                eventsCollection
            ));

            return eventsCollection;
        }

        hexShared<EventHandlersCollection> EventsManager::getHandlersCollection(const ecs_TypeID typeId, const bool create)
        {
            hexLock lock(mHandlersMutex);

            auto pos(mHandlersCollections.find(typeId));
            if (pos != mHandlersCollections.cend())
                return pos->second;


            hexShared<EventHandlersCollection> _handlers(nullptr);

            if (create)
            {
                _handlers = new EventHandlersCollection();
                std::pair<ecs_TypeID, hexShared<EventHandlersCollection>> _pair(
                    typeId,
                    _handlers // Copy
                );
                
            }

            return _handlers; // Copy
        }

        hexShared<ecsIEventHandler> EventsManager::getNextHandler(size_t i, EventHandlersCollection& handlers)
        {
            hexLock lock(handlers.mMutex);

            auto&        handlers_ref(handlers.mHandlers);
            const size_t handlersCount(handlers_ref.size());
            if ((i + 1) > handlersCount || handlers_ref.empty())
                return hexShared<ecsIEventHandler>();

            return handlers_ref.at(i);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
