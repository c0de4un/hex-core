/**
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#ifndef HEX_ECS_TYPES_HPP
#define HEX_ECS_TYPES_HPP

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// INCLUDES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Include hex::core::numeric
#ifndef HEX_CORE_CFG_NUMERIC_HPP
    #include <hex/core/cfg/hex_numeric.hpp>
#endif /// !HEX_CORE_CFG_NUMERIC_HPP

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// TYPES
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
using ecs_TypeID = hex_uint8;
#define ECS_MAX_TYPE_ID std::numeric_limits<hex_uint8>::max()
static constexpr const ecs_TypeID ECS_INVALID_TYPE_ID = 0;

using ecs_ObjectID = hex_uint32;
#define ECS_MAX_OBJECT_ID std::numeric_limits<hex_uint32>::max()
static constexpr const ecs_ObjectID ECS_INVALID_OBJECT_ID = 0;

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

#endif /// !HEX_ECS_TYPES_HPP
