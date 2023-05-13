/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#ifndef HEX_CORE_ID_STORAGE_HPP
#define HEX_CORE_ID_STORAGE_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLDUES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Include hex::core::api
#ifndef HEX_CORE_CFG_API_HPP
    #include <hex/core/cfg/hex_api.hpp>
#endif /// !HEX_CORE_CFG_API_HPP

// Include hex::core::mutex
#ifndef HEX_CORE_CFG_MUTEX_HPP
    #include <hex/core/cfg/hex_mutex.hpp>
#endif /// !HEX_CORE_CFG_MUTEX_HPP

// Include hex::core::vector
#ifndef HEX_CORE_CFG_VECTOR_HPP
    #include <hex/core/cfg/hex_vector.hpp>
#endif /// !HEX_CORE_CFG_VECTOR_HPP

#ifdef HEX_DEBUG /// DEBUG

    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif /// DEBUG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// TYPES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace core
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // IDStorage
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        template <typename V = unsigned int>
        HEX_API class IDStorage final
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
            // FIELDS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            mutable hexMutex mMutex;
            hexVector<V>     mAvailable;
            hexVector<V>     mReserved;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // DELETED
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            IDStorage(const IDStorage&)            = delete;
            IDStorage& operator=(const IDStorage&) = delete;
            IDStorage(IDStorage&&)                 = delete;
            IDStorage& operator=(IDStorage&&)      = delete;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        public:

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // CONSTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            explicit IDStorage(const V capacity = 12, const V reserve = 12)
                :
                mMutex(),
                mAvailable(),
                mReserved()
            {
#ifdef HEX_DEBUG // DEBUG
                assert(capacity > 0 && "IDStorage::construct: invalid capacity");
                assert(reserve <= capacity && "IDStorage::construct: invalid reserve");
#endif // DEBUG

                mAvailable.reserve(capacity);

                mReserved.reserve(capacity);
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // DESTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            ~IDStorage() noexcept
            {
                mAvailable.clear();
                mReserved.clear();
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // METHODS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            V reserve() noexcept
            {
                hexLock lock(mMutex, false);
                lock.try_lock();

#ifdef HEX_DEBUG // DEBUG
                assert(mReserved.size() < hexLimit<V>() && "IDStorage::reserve: maximum size exceeded");
#endif // DEBUG

                V result(0);
                if (!mAvailable.empty())
                {
                    result = mAvailable.back();
                    mAvailable.pop_back();
                }
                else
                    result = mReserved.size() + 1;

                mReserved.push_back(result);

#ifdef HEX_DEBUG // DEBUG
                assert(result > 0 && "IDStorage::reserve: invalid logic, result is 0");
#endif // DEBUG

                return result;
            }

            void put(const V id) noexcept
            {
                hexLock lock(mMutex, false);
                lock.try_lock();

#ifdef HEX_DEBUG // DEBUG
                assert(!mReserved.empty() && "IDStorage::put: invalid logic, reserved ids are empty");
#endif // DEBUG

                V            item(0);
                const size_t reservedCount = mReserved.size();
                for (V i = 0; i < reservedCount; i++)
                {
                    item = mReserved.at(i);
                    if (item == id)
                    {
                        mReserved.erase(mReserved.begin() + i);
                        break;
                    }
                }

                mAvailable.push_back(id);
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        };

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

template <typename V = unsigned int>
using hexIDStorage = hex::core::IDStorage<V>;

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif /// !HEX_CORE_ID_STORAGE_HPP
