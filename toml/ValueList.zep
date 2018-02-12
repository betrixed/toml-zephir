namespace Toml;

/**
 * Description of ValueList
 * Constrains flexible PHP array into taking only one type of data.
 * After assigning the first value, all values must be the same type.
 * @author Michael Rynn
 * 
 */
final class ValueList extends Arrayable
{
    private _type {get}; // string indication of value type
    protected _list;
    
    public final function __construct()
    {
        let this->_list = [];
    }

    public final function offsetSet(int! offset, value) -> void
    {
        var atype;

        let atype = gettype(value);
        if (count(this->_list) === 0) {
            let this->_type = atype;
        }
        else {
            if (this->_type !== atype) {
                throw new XArrayable("Type " . atype . " added to ValueList of " . this->_type);
            }
        }
        if (is_null(offset)) {
            let offset = count(this->_list);
        }
        let this->_list[offset] = value;
    }

    public final function offsetExists(int! offset) -> bool 
    {
        return isset this->_list[offset];
    }

    public final function offsetGet(int! offset) -> var
    {
        return (this->_list[offset]);
    }

    public final function offsetUnset(int! offset) -> void
    {
        unset(this->_list[offset]);
    }

    public final function count() -> int
    {
        return count(this->_list);
    }

    
    public final function get(int! offset, defaultValue = null) -> var
    {
        if isset this->_list[offset] {
            return this->_list[offset];
        }
        else {
            return defaultValue;
        }

    }

    /**
     * Return array copy of everything with nested ValueList object
     * mediation removed.
     * Modification to Config - allow recurse option, 
     * false for no recurse. It can't be passed on.
     * @param bool $recurse
     * @return array
     */
    public final function toArray(bool! recurse = true) -> array
    {
        var result = [];
        var idx, value;
        
        for idx, value in this->_list {
            if (recurse && is_object(value) && (value instanceof \Toml\Arrayable)) {
                
                let result[idx] = value->toArray();
            } else {
                let result[idx] = value;
            }
        }
        return result;
    }
}
