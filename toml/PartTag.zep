/**
* Transcribed from a version adapated from Yosymfony/Toml 
* 
* @author Michael Rynn
*/
namespace Toml;

/*
 * Tracking information for Arrayable tag property
 */
class PartTag
{
    public partKey; // String key part
    public isAOT; // Update in parse for TOM04 checks
    public objAOT; // true for TableList, false for Table
    public implicit; // implicit flag
    
    public function __construct(var key, bool! objAOT) {
        let this->partKey = key;
        let this->isAOT = objAOT;
        let this->objAOT = objAOT;
        let this->implicit = false;
    }
}