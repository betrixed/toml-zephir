// Exception class XArrayable.zep

namespace Yosy;

/**
 * XArrayable, for general exceptions
 * in this namespace.
 *
 * @author michael
 */
class XArrayable extends \Exception
{
    public function __construct(string! msg) {
        parent::__construct(msg);
    }
}