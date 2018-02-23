namespace Toml;

/**
 * Description of ValueList
 * Constrains flexible PHP array into taking only one type of data.
 * After assigning the first value, all values must be the same type.
 * @author Michael Rynn
 * 
 */
final class ValueList implements Arrayable
{
    private _type {get}; // string indication of value type
    protected _list;
    private _tag;


    public final function __construct()
    {
        let this->_list = [];
    }

    public function allowType(string! type) -> boolean {
        if empty(this->_type) && !empty(type) {
            return true;
        }
        else {
            return (type === this->_type);
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
    
    public final function offsetSet(var offset, value) -> void
    {
        var vtype, ct;
        let ct = count(this->_list);
        let vtype = gettype(value);

        if ct === 0 {
            let this->_type = vtype;
        }
        elseif this->_type !== vtype {
            throw new XArrayable("Type " . vtype . " cannot be added to ValueList of " . this->_type);
        }
        if empty offset {
            let offset = ct;
        }
        elseif gettype(offset) !== "integer" {
            throw new XArrayable("ValueList only takes integer offsets");
        }
        let this->_list[offset] = value;
    }

    public final function offsetExists(int offset) -> bool 
    {
        return isset this->_list[offset];
    }

    public final function offsetGet(int offset) -> var
    {
        return (this->_list[offset]);
    }

    public final function offsetUnset(int offset) -> void
    {
        unset(this->_list[offset]);
    }

    public final function count() -> int
    {
        return count(this->_list);
    }

    
    public final function get(int offset, defaultValue = null) -> var
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
