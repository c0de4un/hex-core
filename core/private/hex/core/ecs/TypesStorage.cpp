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
#ifndef HEX_ECS_TYPES_STORAGE_HPP
    #include <hex/core/ecs/TypesStorage.hpp>
#endif /// !HEX_ECS_TYPES_STORAGE_HPP

#ifdef HEX_DEBUG /// DEBUG

    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif /// DEBUG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// TypesStorage
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace ecs
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // FIELDS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        TypesStorage* TypesStorage::mInstance(nullptr);

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTOR & DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        TypesStorage::TypesStorage()
            : mTypeIDs(TypesStorage::DEFAULT_CAPACITY)
        {
        }

        TypesStorage::~TypesStorage() noexcept = default;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void TypesStorage::Create()
        {
#ifdef HEX_DEBUG // DEBUG
            assert(!mInstance && "TypesStorage::Create: already created");
#endif // DEBUG

            if (!mInstance)
                mInstance = new TypesStorage();
        }

        void TypesStorage::Terminate()
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "TypesStorage::Terminate: already terminated, fix logic");
#endif // DEBUG

            delete mInstance;
            mInstance = nullptr;
        }

        ecs_TypeID TypesStorage::generateTypeID()
        {
#ifdef HEX_DEBUG // DEBUG
            assert(mInstance && "TypesStorage::generateTypeID: instance if null, check logic");
#endif // DEBUG

            return mInstance->mTypeIDs.reserve();
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
