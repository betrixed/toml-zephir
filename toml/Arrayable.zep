namespace Toml;

/**
 * Provides array syntax like access to get and set PHP object properties, and
 * restricted conversions to and from array via merge and toArray.
 * The Tag property is for possible management data, without interfering with
 * planned storage implementation.
 * 
 * @author Michael Rynn
 */

interface Arrayable extends \ArrayAccess, \Countable {
    
    public function toArray() -> array;
    public function getTag() -> var;
    public function setTag(var tag) -> void;

}