namespace Yosy;

/**
 * Description of Box
 * Enable pass around any array type as a reference
 * @author Michael Rynn
 */
final class Box
{
    public _me;
    
    public final function __construct(var me) {
        let this->_me = me;
    }
}