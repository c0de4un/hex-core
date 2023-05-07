/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#ifndef HEX_CORE_CFG_MUTEX_HPP
#define HEX_CORE_CFG_MUTEX_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Include hex::core::cfg::platform
#ifndef HEX_CORE_CFG_PLATFORM_HPP
    #include "hex_platform.hpp"
#endif /// !HEX_CORE_CFG_PLATFORM_HPP

// Platform-specific mutex
#if defined(HEX_WINDOWS) // WINDOWS

    // Include hex::win::WinMutex
    #ifndef HEX_WIN_MUTEX_HPP
        #include <hex/windows/async/WinMutex.hpp>
    #endif /// !HEX_WIN_MUTEX_HPP
    using hexMutex = hex::win::WinMutex;

#elif defined(HEX_ANDROID)

    // Include hex::android::AndroidMutex
    #ifndef HEX_ANDROID_MUTEX_HPP
        #include <hex/android/async/AndroidMutex.hpp>
    #endif /// !HEX_ANDROID_MUTEX_HPP
using hexMutex = hex::android::AndroidMutex;

#elif defined(HEX_LINUX)

    // Include hex::linux::LinuxMutex
    #ifndef HEX_LINUX_MUTEX_HPP
        #include <hex/linux/async/LinuxMutex.hpp>
    #endif /// !HEX_LINUX_MUTEX_HPP
    using hexMutex = hex::linux::LinuxMutex;

#else
    #error "hex_mutex.hpp - undefined platform, configuration required"
#endif

// Include hex::core::SpinLock
#ifndef HEX_CORE_SPIN_LOCK_HPP
    #include <hex/core/async/SpinLock.hpp>
#endif /// !HEX_CORE_SPIN_LOCK_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif /// !HEX_CORE_CFG_MUTEX_HPP
