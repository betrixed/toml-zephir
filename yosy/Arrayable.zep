namespace Yosy;

/**
 * Provides array syntax like access to get and set PHP object properties, and
 * restricted conversions to and from array via merge and toArray.
 * The Tag property is for possible management data, without interfering with
 * planned storage implementation.
 * 
 * @author Michael Rynn
 */

abstract class Arrayable implements \ArrayAccess, \Countable {
    private _tag;
    
    public function setTag(any) {
        let this->_tag = any;
    }
    public function getTag() {
        return this->_tag;   
    }
    
    abstract public function toArray();

}