/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#ifndef HEX_CORE_SHARED_POINTER_HPP
#define HEX_CORE_SHARED_POINTER_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Include hex::core::MemoryManager
#ifndef HEX_CORE_MEMORY_MANAGER_HPP
    #include <hex/core/memory/MemoryManager.hpp>
#endif /// !HEX_CORE_MEMORY_MANAGER_HPP

// Include hex::core::IReferenceUser
#ifndef HEX_CORE_I_REFERENCE_USER_HXX
    #include <hex/core/memory/IReferenceUser.hxx>
#endif /// !HEX_CORE_I_REFERENCE_USER_HXX

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// TYPES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace core
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // SharedPointer
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        template <typename T>
        HEX_API class SharedPointer final : public IReferenceUser
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

            T* mAddress;

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // METHODS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            inline void reserve()
            {
                if (!mAddress)
                    return;

                hexMemory* const memoryManager(hexMemory::getInstance());

                if (memoryManager)
                    memoryManager->addReferenceUser(static_cast<void*>(mAddress), static_cast<IReferenceUser*>(this));
            }

            inline void release() noexcept
            {
                if (!mAddress)
                    return;

                hexMemory* const memoryManager(hexMemory::getInstance());

                if (memoryManager)
                {
                    try
                    {
                        memoryManager->removeReferenceUser(static_cast<void*>(mAddress), static_cast<IReferenceUser*>(this));
                    }
                    catch (...)
                    {
                        // void
                    }
                }
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        public:

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // CONSTRUCTORS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            explicit SharedPointer(T* pAddress = nullptr)
                :
                mAddress(pAddress)
            {
                reserve();
            }

            SharedPointer(const SharedPointer<T>& other)
                :
                mAddress(other.mAddress)
            {
                reserve();
            }

            SharedPointer(SharedPointer<T>&& other)
                : mAddress(other.mAddress)
            {
                other.mAddress = nullptr;
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // DESTRUCTOR
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            virtual ~SharedPointer() noexcept
            {
                release();
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // GETTERS & SETTERS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            T* get() noexcept
            {
                return mAddress;
            }

            long use_count() const noexcept
            {
                if (!mAddress)
                    return 0;

                try
                {
                    hexMemory* const memoryManager(hexMemory::getInstance());

                    if (memoryManager)
                        return memoryManager->getReferenceCount(mAddress);
                }
                catch (...)
                {
                    return 0;
                }
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // OVERRIDE.IReferenceBlock
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            void onDeleteObject() final
            {
                T* address(mAddress);
                mAddress = nullptr;

                delete address;
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // METHODS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            void reset(T* pAddress = nullptr)
            {
                release();

                mAddress = pAddress;

                reserve();
            }

            bool equal(T* pAddress) const noexcept
            {
                return mAddress == pAddress;
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            // OPERATORS
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

            T* operator->() noexcept
            {
                return mAddress;
            }

            void operator=(T* pAddress)
            {
                reset(pAddress);
            }

            bool operator==(T* pAddress) const noexcept
            {
                return equal(pAddress);
            }

            SharedPointer<T> operator=(const SharedPointer<T>& other)
            {
                return SharedPointer<T>(other);
            }

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        };

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

template <typename T>
using hexShared = hex::core::SharedPointer<T>;

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif /// !HEX_CORE_SHARED_POINTER_HPP
