/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#ifndef HEX_CORE_CFG_PLATFORM_HPP
#define HEX_CORE_CFG_PLATFORM_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#if !defined(HEX_PLATFORM_DEFINED) || HEX_PLATFORM_DEFINED == 0

    // WINDOWS
    #if defined( MINGW ) || defined( MINGGW32 ) || defined( MINGW64 ) || defined( WIN32 ) || defined( WIN64 ) || defined( WINDOWS ) || defined( MSVC )
        #define HEX_WINDOWS
    #elif defined( __linux ) || defined( _linux ) || defined( _linux_ ) || defined( __linux__ ) || defined( LINUX )
        // LINUX
        #define HEX_LINUX
    #elif defined( ANDROID ) || defined( _android_ ) || defined( __android__ ) || defined( _android ) || defined( __android )
        // ANDROID
        #define HEX_ANDROID
    #else
        #error "hex_platform.hpp - configuration required"
    #endif

#endif

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif /// !HEX_CORE_CFG_PLATFORM_HPP
