/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#ifndef HEX_CORE_CFG_API_HPP
#define HEX_CORE_CFG_API_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Include hex::core::platform
#ifndef HEX_CORE_CFG_PLATFORM_HPP
    #include "hex_platform.hpp"
#endif /// !HEX_CORE_CFG_PLATFORM_HPP

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// API
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#if defined( HEX_SHARED ) // SHARED Library

#if defined( HEX_EXPORT )
    #define HEX_API __declspec( dllexport ) // EXPORT
#else
    #define HEX_API __declspec( dllimport ) // IMPORT
#endif

#elif defined( HEX_STATIC ) // STATIC Library
    #define HEX_API /** void **/
#else
    #define HEX_API /** void **/
#endif

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// REFLECTION
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#define HEX_STRUCT
    #define HEX_CLASS
#define HEX_INTERFACE

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// DEBUG
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#if defined( DEBUG ) || defined( HEX_DEBUG )
    #define HEX_NOEXCEPT
#else
    #define HEX_NOEXCEPT noexcept
#endif

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif /// !HEX_CORE_CFG_API_HPP
