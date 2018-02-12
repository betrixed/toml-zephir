
/*
 * @author Michael Rynn
 */

/**
 * Hold String keyed data in PHP internal object properties table
 * @author Michael Rynn
 */

namespace Toml;

/**
 * Converts all keys to string, stores values as internal php object property.
 * Handles TableList object as values.
 * Is Recursive for Table objects as value.
 * 
 */
final class Table extends Arrayable
{
     //const PATH_DELIMITER = ".";

    /**
    * @param array 
    */
    public final function mergeArray(array! kv) -> void {
    	var key, value;
    	for key,value in kv {
            this->offsetSet(key, value);
        }
    }
    
    /**
     * Associate management properties to private tag 
     * @param type $any
     */
    
    public final function __construct(array aval = null)
    { 
        if (!is_null(aval)) {
            this->mergeArray(aval);
        }
    }

    /**
     * This implements the array-access [],
     * but is not called for property access.
     * Looks like a good place to 
     * substitute global defines for ${defined}
     * @param type $index
     * @param type $value
     * Does not get called when values set as ->property
     * as this uses magic __set
     */
    
    public final function offsetSet(string! index, var value) -> void
    {
        if (is_array(value)) {
            let this->{index} = new Table(value);
        } else {
            let this->{index} = value;
        }
    }
	

    public final function offsetExists(string! index) ->  bool
    {
        return isset this->{index};
    }

    public final function offsetGet(string! index) -> var
    {
        return this->{index};
    }

    public final function offsetUnset(string! index) -> void
    {
        let this->{index} = null;
    }

    /**
     * Count number of accessible items in internal object properties
     */
    public final function count() -> int
    {
        return count(get_object_vars(this));
    }

    /**
    * Return object property value from nested objects
    * path separator is '.'
    */
    public final function path(string! path, var defaultValue = null) -> var
    {
        if isset this->{path} {
            return this->{path};
        }

        var delimiter = ".";

        var level = this;
        var keys = explode(delimiter, path);

        while !empty keys {
            var key = array_shift(keys);
            if !isset level->{key} {
                break;
            }

            if empty keys {
                return level->{key};
            }
            let level = level->{key};

            if empty level {
                break;
            }
        }
        return defaultValue;
    }

    public final function get(string! index, var defaultValue = null) -> var
    {
        if isset this->{index} {
            return this->{index};
        }
        return defaultValue;
    }

    /**
     * Modification to Config - allow recurse option, 
     * false for no recurse. It can't be passed on.
     * @param bool $recurse
     * @return array
     */
    public final function toArray(bool! recurse = true) -> array
    {
        var result, key, value;

        let result = [];
        
        for key,value in get_object_vars($this) {
            if (recurse && is_object(value) && (value instanceof \toml\arrayable)) {
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
    
    public final function treeIterateValues(var callback) -> void
    {
    	var key, value;
        if (!is_callable(callback)) {
            throw new Xarrayable("Need callback argument");
        }
        for key,value in get_object_vars($this) {
            if (is_object(value) && (is_a(value, "\\Toml\\Table") || is_a(value, "\\Toml\\Table"))) {
                value->treeIterateValues(callback);
            } else {
                let this->{key} = call_user_func(callback, value);
            }
        }
    }

}