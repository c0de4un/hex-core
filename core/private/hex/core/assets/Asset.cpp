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
#ifndef HEX_CORE_ASSET_HPP
    #include <hex/core/assets/Asset.hpp>
#endif /// !HEX_CORE_ASSET_HPP

#ifdef HEX_LOGGING // LOG

    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif // LOG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// ASSET
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace core
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTORS & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        Asset::Asset(const hexString name)
            :
            mState(STATE_NONE),
            mUsersCount(0),
            mStateMutex(),
            mName(name)
        {
        }

        Asset::~Asset() noexcept = default;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // PUBLIC OVERRIDE: IAsset.GETTERS & SETTERS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool Asset::isLoaded() const noexcept
        {
            const auto _state(mState.load());

            return _state > STATE_NONE;
        }

        bool Asset::isLoading() const noexcept
        {
            const auto _state(mState.load());

            return _state == STATE_LOADING;
        }

        bool Asset::isUnloading() const noexcept
        {
            const auto _state(mState.load());

            return _state == STATE_UNLOADING;
        }

        size_t Asset::countUsers() const noexcept
        {
            const auto _result(mUsersCount.load());

            return _result;
        }

        const hexString Asset::getName() const noexcept
        {
            return mName;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // PUBLIC OVERRIDE: IAsset.METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool Asset::Load()
        {
#ifdef HEX_LOGGING // LOG
            hexString _msg("Asset#");
            _msg += mName;
            _msg += "::Load";
            hexLog::Debug(_msg.c_str());
#endif // LOG

            hexLock stateLock(mStateMutex);
            if (isLoading() || isLoaded())
                return true;
            mState = STATE_LOADING;
            stateLock.unlock();


            return onLoad();
        }

        void Asset::Unload()
        {
#ifdef HEX_LOGGING // LOG
            hexString _msg("Asset#");
            _msg += mName;
            _msg += "::Unload";
            hexLog::Debug(_msg.c_str());
#endif // LOG

            hexLock stateLock(mStateMutex);

#ifdef HEX_DEBUG // DEBUG
            if (mUsersCount.load())
            {
                _msg = "Asset#";
                _msg += mName;
                _msg += "::Unload";
                hexLog::Warning(_msg.c_str());
            }
#endif // DEBUG

            if (mUsersCount.load() || isUnloading() || !isLoaded())
                return;

            mState = STATE_UNLOADING;
            stateLock.unlock();

            onUnload();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // PROTECTED.METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool Asset::onLoad()
        {
            mState = STATE_LOADED;

            return true;
        }

        void Asset::onUnload()
        {
            mState = STATE_NONE;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
