/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#ifndef HEX_CORE_I_RENDERER_HXX
#define HEX_CORE_I_RENDERER_HXX

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Include hex::core::api
#ifndef HEX_CORE_CFG_API_HPP
    #include <hex/core/cfg/hex_api.hpp>
#endif /// !HEX_CORE_CFG_API_HPP

// Include hex::memory
#ifndef HEX_CORE_CFG_MEMORY_HPP
    #include <hex/core/cfg/hex_memory.hpp>
#endif /// !HEX_CORE_CFG_MEMORY_HPP

// Include hex::core::Shader
#ifndef HEX_CORE_SHADER_HPP
    #include <hex/core/assets/Shader.hpp>
#endif /// !HEX_CORE_SHADER_HPP

// Include hex::core::BatchingRequest
#ifndef HEX_CORE_BATCHING_REQUEST_HPP
    #include <hex/core/render/BatchingRequest.hpp>
#endif /// !HEX_CORE_BATCHING_REQUEST_HPP

// Include hex::core::Batch
#ifndef HEX_CORE_BATCH_HPP
    #include <hex/core/render/Batch.hpp>
#endif /// !HEX_CORE_BATCH_HPP

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// FORWARD-DECLARATIONS
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Forward-Declare hex::core::IRenderListener
#ifndef HEX_CORE_I_RENDERER_LISTENER_DECL
    #define HEX_CORE_I_RENDERER_LISTENER_DECL
    namespace hex { namespace core { class IRendererListener; } }
    using hexIRendererListener = hex::core::IRendererListener;
#endif /// !HEX_CORE_I_RENDERER_LISTENER_DECL

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// IRenderer
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace core
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        HEX_API class IRenderer
        {

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // META
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            HEX_INTERFACE

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        public:

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // DESTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            virtual ~IRenderer() noexcept = default;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // METHODS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            virtual void registerListener(hexShared<hexIRendererListener>&) = 0;
            virtual void unregisterListener(hexIRendererListener* const)    = 0;

            virtual hexShared<hexShader> createShader(
                const hexString name,
                const unsigned char shaderType,
                const hexString* const sourceFile,
                const hexString* const sourceCode
            ) = 0;

            virtual hexShared<hexBatchingRequest> createBatchRequest() = 0;

            virtual hexShared<hexBatch> registerBatchable(hexShared<hexBatchingRequest>& pRequest) = 0;
            virtual void unregisterBatchable(ecs_ObjectID batchID)                                 = 0;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        };

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

using hexIRenderer = hex::core::IRenderer;

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif /// !HEX_CORE_I_RENDERER_HXX
