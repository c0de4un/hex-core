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
#ifndef HEX_CORE_LOG_HPP
    #include <hex/core/metrics/Log.hpp>
#endif /// !HEX_CORE_LOG_HPP

// Include hex::core::ILogger
#ifndef HEX_CORE_I_LOGGER_HXX
    #include <hex/core/metrics/ILogger.hxx>
#endif /// !HEX_CORE_I_LOGGER_HXX

// Include hex::core::cfg::debug
#ifndef HEX_CORE_CFG_DEBUG_HPP
    #include <hex/core/cfg/hex_debug.hpp>
#endif /// !HEX_CORE_CFG_DEBUG_HPP

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Log
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace core
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // FIELDS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        Log::logger_ptr Log::mLogger(nullptr);

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        Log::Log() noexcept  = default;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        Log::~Log() noexcept = default;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void Log::Info(const char* const msg) noexcept
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mLogger && "Log::Info: instance not set");
#endif // DEBUG

            mLogger->printInfo(msg);
        }

        void Log::Debug(const char* const msg) noexcept
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mLogger && "Log::Debug: instance not set");
#endif // DEBUG

            mLogger->printDebug(msg);
        }

        void Log::Warning(const char* const msg) noexcept
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mLogger && "Log::Warning: instance not set");
#endif // DEBUG

            mLogger->printWarning(msg);
        }

        void Log::Error(const char* const msg) noexcept
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mLogger && "Log::Error: instance not set");
#endif // DEBUG

            mLogger->printError(msg);
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
