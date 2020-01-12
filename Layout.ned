//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package vanet.simulations;
import vanet.nodes.RSU;
import vanet.Scenario1;
import vanet.nodes.Mobile;
import vanet.nodes.Tower;

network Layout extends Scenario1
{
    submodules:

        rsu3: RSU {
            @display("p=221,128;i=veins/sign/yellowdiamond;is=vs");
        }
        rsu4: RSU {
            @display("p=74,140;i=veins/sign/yellowdiamond;is=vs");
        }
        tower1: Tower {
            @display("p=142,140;i=device/antennatower");
        }        
        Mobile1: Mobile {
            @display("p=123,69;i=device/pocketpc");
        }
      

}
