
/**
 * @author Michael Rynn
 */

namespace Toml;

/**
 * This is more general, no frills, object wrap of a PHP array
 * It is more inefficient than a bare PHP array.
 * The internal $_store is public for easy iteration.
 * Any PHP key type is allowed. 
 * Strict TOML04 - says integer key values  must 
 * be converted to strings!
 * 
 * Hence if we parsed an integer key, and converted it, and set the key as a string
 * and then extracted the key later, it would of integer type again, due to PHP's
 * convert everything that looks like an integer, to an integer,  for Array keys.
 * "1" and intval(1) are the PHP same key,
 * stored as binary integer. Hash algorithms are faster on binary integers, because the Hash,
 * usually becomes a binary integer value, restricted to hash table storage.
 * Quite often integer values are what is intended.

 * It makes sense for internet HTML forms convenience, where everything is text,
 * and numeric values are returned as string. 

 * If the numeric string is beyond an upper limit of representation it remains a string,
 * and in this case can never be an integer.
 * So if this class was used as TOML tables, all integer keys may need to be converted back to 
 * string on retrieval.
 * This class gives a standard "referenced" array as object without a reference operator &
 */
final class KeyTable implements Arrayable
{
    public _store;
    private _tag;

    public final function __construct(var seed = null)
    {
        if is_object(seed) && (seed instanceof \Toml\KeyTable) {
            var key, value;
            for key,value in seed->_store {
                let this->_store[key] = value;
            }
        }
        elseif gettype(seed) === "array" {
            var key, value;
            for key, value in seed {
                let this->_store[key] = value;
            }
        } else {
            var init = [];
            let this->_store = init;
        }
    }
    public final function getTag() -> var
    {
        return this->_tag;
    }
    public final function setTag(var tag) -> void 
    {
        let this->_tag = tag;
    }
    /**
     * @param type $index
     */
    public final function offsetSet(var index, var value) -> void
    {
        //echo "offsetSet index " . index . " value {" . value . "}" . ": " . gettype(value) . PHP_EOL;
        let this->_store[index] = value;
    }

    public final function offsetExists(var index) -> bool
    {
        return isset this->_store[index];
    }

    public final function offsetGet(var index) -> var
    {
        return this->_store[index];
    }

    public final function offsetUnset(var index) -> void
    {
        unset this->_store[index];
    }

    public final function count() -> int
    {
        return count($this->_store);
    }

    public final function get(var index, defaultValue = null)
    {
        return isset  this->_store[ index] ?  this->_store[ index] :  defaultValue;
    }

    /**
     * Return array copy of everything with nested KeyTable object
     * mediation removed.
     * Modification to Config - allow recurse option, 
     * false for no recurse. It can't be passed on.
     * @param bool $recurse
     * @return array
     */
    public final function toArray(bool recurse = true) -> array
    {
        var result = [];
        var key,value;
        if !empty this->_store {
            for key, value in this->_store {
                if (recurse && is_object(value) && (value instanceof \Toml\Arrayable)) {
                    let result[key] = value->toArray();
                } else {
                    let result[key] = value;
                }
            }
        }
        return result;
    }

    /**
    * @param myKeyTable should be a KeyTable
    * @return KeyTable
    */
    public final function merge(kt) -> var
    {
        return this->_merge(kt);
    }

    /**
     * Merge values in $config, into the properties of $instance
     * 
     * @param \Yosy\KeyTable $config
     * @param \Yosy\KeyTable  $instance
     * @return \Yosy\KeyTable 
     */
    protected final function _merge(kt, target = null) -> var
    {
        if (!is_object(target)) {
            let target = this;
        }
        var key, value;
        var myObj;

        for key, value in kt ->_store {
        	if !fetch myObj, target->_store[key] {
            	let myObj = null;
            }

            if (is_object(myObj)) {
                // Are both objects Mergeable ? 
                if ((myObj instanceof \Yosy\KeyTable) && is_object(value) && (value instanceof \Toml\KeyTable)) {
                    this->_merge(value, myObj);
                    continue;
                }
            }
            let target->_store[key] = value;
        }
        return target;
    }

}
