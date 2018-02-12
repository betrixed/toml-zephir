namespace Toml;

/**
 * Enable boxing an array type to emulate a reference
 * @author Michael Rynn
 */
final class Box
{
    public _me;
    
    public final function __construct(var me) {
        let this->_me = me;
    }
}