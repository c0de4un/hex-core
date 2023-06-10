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
#ifndef HEX_CORE_MATERIAL_HPP
    #include <hex/core/assets/Material.hpp>
#endif /// !HEX_CORE_MATERIAL_HPP

#ifdef HEX_LOGGING // LOG

    #ifndef HEX_CORE_CFG_DEBUG_HPP
        #include <hex/core/cfg/hex_debug.hpp>
    #endif /// !HEX_CORE_CFG_DEBUG_HPP

#endif // LOG

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Material
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

namespace hex
{

    namespace core
    {

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // CONSTRUCTORS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        Material::Material(const hexString name)
            :
            Asset(name),
            mSlotsMutex(),
            mSlots()
        {
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // DESTRUCTOR
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        Material::~Material() noexcept = default;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // IMaterial: PUBLIC GETTERS & SETTERS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        hexShared<Asset> Material::getSlot(const hexString& slotName)
        {
            hexLock lock(mSlotsMutex);

            return mSlots[slotName];
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // IMAterial: PUBLIC METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        void Material::attachSlot(const hexString& slotName, hexAsset* const pItem)
        {
            hexLock lock(mSlotsMutex);

            mSlots[slotName] = hexShared<Asset>(pItem);
        }

        void Material::detachSlot(const hexString& slotName)
        {
            hexLock lock(mSlotsMutex);

            mSlots[slotName] = nullptr;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        // Asset: PROTECTED METHODS
        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

        bool Material::onLoad()
        {
            const auto end_iter(mSlots.cend());
            auto       iter(mSlots.begin());
            bool       slotLoaded(false);
            while (iter != end_iter)
            {
                auto& slot(iter->second);
                if (slot.get())
                {
                    slotLoaded = slot->Load();

#ifdef HEX_DEBUG // DEBUG
                    assert(slotLoaded && "Material::onLoad: failed to load slot");
#endif // DEBUG
                }
                iter++;
            }

            mState = STATE_LOADED;

            return true;
        }

        void Material::onUnload()
        {
            const auto end_iter(mSlots.cend());
            auto       iter(mSlots.begin());
            bool       slotLoaded(false);
            while (iter != end_iter)
            {
                auto& slot(iter->second);
                if (slot.get())
                    slot->Unload();

                iter++;
            }

            mState = STATE_NONE;
        }

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    }

}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
