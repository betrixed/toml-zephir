namespace Yosy;

/**
 * Description of ValueList
 * Constrains flexible PHP array into taking only one type of data.
 * After assigning the first value, all values must be the same type.
 * @author Michael Rynn
 * 
 */
class ValueList extends Arrayable
{
    private _type {get}; // string indication of value type
    protected _list;
    
    public final function __construct()
    {
        let this->_list = [];
    }

    public function offsetSet(int! offset, value)
    {
        atype = gettype(value);
        if (count(this->_list) === 0) {
            let this->_type = atype;
        }
        else {
            if (this->_type !== atype) {
                throw new XArrayable('Type ' . atype . ' added to ValueList of ' . this->_type);
            }
        }
        if (is_null(offset)) {
            offset = count(this->_list);
        }
        let this->_list[offset] = value;
    }

    public function offsetExists(int! offset): bool
    {
        return isset this->_list[offset];
    }

    public function offsetGet(int! offset)
    {
        return (this->_list[offset]);
    }

    public function offsetUnset(int! offset)
    {
        unset(this->_list[offset]);
    }

    public function count(): int
    {
        return count(this->_list);
    }

    
    public function get(int! offset, defaultValue = null)
    {
        if isset $this->_list[offset] {
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
    public function toArray(bool! recurse = true): array
    {
        let result  = [];
        foreach (this->_list as idx => value) {
            if (recurse && is_object(value) && (value instanceof \Yosy\Arrayable)) {
                
                let result[idx] = value->toArray();
            } else {
                let result[idx] = value;
            }
        }
        return result;
    }
}
