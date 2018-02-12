
/**
 * @author Michael Rynn
 */

namespace Yosy;

/**
 * This is more general, no frills, object wrap of a PHP array
 * It is more inefficient than a bare PHP array.
 * The internal $_store is public for easy iteration.
 * Any PHP key type is allowed. 
 * Aim is to have a "referenced" array as object without a reference operator &
 */
final class KeyTable extends Arrayable
{

    public _store;

    public final function __construct(array seed = null)
    {
        var key, value;
        if (!is_null(seed)) {
        	for key, value in seed {
                let this->_store[key] = value;
            }
        } else {
            let this->_store = [];
        }
    }

    /**
     * @param type $index
     */
    public final function offsetSet(index, value) -> void
    {
        let this->_store[index] = value;
    }

    public final function offsetExists(index) -> bool
    {
        return isset this->_store[index];
    }

    public final function offsetGet(index) -> var
    {
        return this->_store[index];
    }

    public final function offsetUnset(index) -> void
    {
        unset this->_store[index];
    }

    public final function count() -> int
    {
        return count($this->_store);
    }

    public final function get(index, defaultValue = null)
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
        for key, value in this->_store {
            if (recurse && is_object(value) && (value instanceof \Yosy\Arrayable)) {
                let result[key] = value->toArray();
            } else {
                let result[key] = value;
            }
        }
        return result;
    }

    /** iterate the config tree for $callback on values
     * 
     * @param type $callback
     */
    public final  function treeIterateValues(callback) -> void
    {
        if (!is_callable(callback)) {
            throw new {yosy\xarrayable}("Needs function for callback");
        }
        var key, value;
        for key, value in get_object_vars($this) {
            if (is_object(value) && (is_a(value, "\\Yosy\\KeyTable"))) {
                value->treeIterateValues(callback);
            } else {
                let this->_store[key] = \call_user_func(callback, value);
            }
        }
    }
    /**
    * @param myKeyTable should be a KeyTable
    * @return KeyTable
    */
    public final function merge( kt) -> var
    {
        return this->_merge(kt);
    }

    /**
     * Merge values in $config, into the properties of $instance
     * TableList objects are added together.
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
                if ((myObj instanceof \Yosy\KeyTable) && is_object(value) && (value instanceof \Yosy\KeyTable)) {
                    this->_merge(value, myObj);
                    continue;
                }
            }
            let target->_store[key] = value;
        }
        return target;
    }

}
