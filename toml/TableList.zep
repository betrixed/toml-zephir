
/*
 * @author Michael Rynn
 */

/**
 * A dumb list of Table objects.
 * This object is limited to storing Table objects in numeric
 * zero-indexed array
*/
namespace Toml;
use Toml\KeyTable;

final class TableList implements Arrayable {
    // This seperates key path component for nested Arrayable objects.
    private _list;
    private _tag;

    public final function __construct(array list = null) {
       if empty list {
            //let this->_list =  [];
            let this->_list[0] = new KeyTable();
        }
        else {
            //TODO: check all members are Table objects, and no key:values
            let this->_list = list;
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
     * return offset to last Table *
     * @return int
     */
    public final function getEndIndex() -> int {
        return count(this->_list) - 1;
    }
    /**
     * Return last Table object
     * @return \Toml\Table
     */
    public final function getEndTable() -> var {
        return this->_list[ count(this->_list) - 1 ];
    }
    
    public final function getTables() -> array {
        return this->_list;
    }
    /**
     * Return a new table added to the end of the list
     * @return \Toml\Table
     */
    public final function newTable() -> var {
        var item; 
        let item = new KeyTable();
        let this->_list[] = item;
        return item;
    }

    /** 
    Add tables from another TableList object
    */
    public final function addTables(var obj) -> void {
        let this->_list = array_merge(this->_list, obj->_list);
    }
    /**
     * This implements the array-access [],
     * Strictly don't even want to provide such write access
     * so this may just throw exception in future
     * @param type $index
     * @param type $value
     */
    public final function offsetSet(int! index, var value) -> void {
        if (!is_a(value, "\\Toml\\KeyTable")) {
            throw new XArrayable("TableList Value must be \\Toml\\KeyTable");
        }
        let this->_list[index] = value;
    }

    public final function offsetExists(int! index) -> bool {
        return isset this->_list[index];
    }

    public final function offsetGet(int! index) -> var {
        return this->_list[index];
    }

    /**
     * May throw exception in future
     * @param type $index
     */
    public final function offsetUnset(int! index) -> void {

        unset this->_list[index];
    }

    public final function count() -> int {
        return count(this->_list);
    }

    /**
     * Return a copy of the TableList as array.
     * Default $recurse is true to return Table content instead of KeyTable object
     * @param bool $recurse
     * @return array
     */
    public final function toArray(bool! recurse = true) -> array {
        var result = array_fill(0, count(this->_list), null);
        var idx, value;
        for idx, value in this->_list {
            if (recurse) {
                let result[idx] = value->toArray();
            } else {
                let result[idx] = value;
            }
        }
        return result;
    }
    
}


