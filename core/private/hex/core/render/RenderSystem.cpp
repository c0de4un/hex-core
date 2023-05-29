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
#ifndef HEX_CORE_RENDER_SYSTEM_HPP
    #include <hex/core/render/RenderSystem.hpp>
#endif /// !HEX_CORE_RENDER_SYSTEM_HPP

// Include hex::core::IRendererListener
#ifndef HEX_CORE_I_RENDERER_LISTENER_HXX
    #include <hex/core/render/IRendererListener.hxx>
#endif /// !HEX_CORE_I_RENDERER_LISTENER_HXX

#ifdef HEX_LOGGING // LOG

    // Include hex::core::debug
    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif // LOG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// RenderSystem
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace core
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // FIELDS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        hexMutex                RenderSystem::mInstanceMutex;
        hexShared<RenderSystem> RenderSystem::mInstance(nullptr);

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        RenderSystem::RenderSystem()
            :
            System(static_cast<ecs_TypeID>(hexESystems::RENDER)),
            mListenersMutex(),
            mListeners()
        {
        }

        RenderSystem::~RenderSystem() noexcept = default;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // GETTERS & SETTERS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        hexShared<RenderSystem> RenderSystem::getInstance() noexcept
        {
            hexLock lock(mInstanceMutex);

            return mInstance; // Copy
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void RenderSystem::Terminate() noexcept
        {
#ifdef HEX_LOGGING // LOG
            hexLog::Info("RenderSystem::Terminate");
#endif // LOG

            hexLock lock(mInstanceMutex, true);
            mInstanceMutex.try_lock();

            mInstance = nullptr;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // OVERRIDE: IRenderer
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void RenderSystem::registerListener(RenderSystem::listener_ptr_t& pListener)
        {
#ifdef HEX_DEBUG // DEBUG
            assert(pListener.get() && "RenderSystem::registerListener: null given");
#endif // DEBUG

            hexLock lock(mListenersMutex);

            for (RenderSystem::listener_ptr_t& listener : mListeners)
            {
                if (!listener.get())
                {
                    listener.reset(pListener.get());
                    return;
                }
            }

            mListeners.push_back(pListener);
        }

        void RenderSystem::unregisterListener(hex_IRendererListener* const pListener)
        {
#ifdef HEX_DEBUG // DEBUG
            assert(pListener && "RenderSystem::unregisterListener: null given");
#endif // DEBUG

            hexLock lock(mListenersMutex);

            const auto end_iter(mListeners.cend());
            auto iter(mListeners.begin());
            while (iter != end_iter)
            {
                RenderSystem::listener_ptr_t& listener((*iter));
                if (listener == pListener)
                {
                    listener.reset(nullptr);
                    return;
                }

                iter++;
            }
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
