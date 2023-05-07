/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#if !defined(HEX_LOGGING) || !HEX_LOGGING
    #error "hex_debug - logging-headers used without logging enabled"
#endif

#ifndef HEX_CORE_CFG_DEBUG_HPP
#define HEX_CORE_CFG_DEBUG_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#if HEX_DEBUG // DEBUG

    // Include assertions
    #include <cassert>

#endif // DEBUG

// Include STL exception
#include <exception>

// Include STL string
#include <string>

// Include hex::core::Log
#ifndef HEX_CORE_LOG_HPP
    #include <hex/core/metrics/Log.hpp>
#endif /// !HEX_CORE_LOG_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif /// !HEX_CORE_CFG_DEBUG_HPP
