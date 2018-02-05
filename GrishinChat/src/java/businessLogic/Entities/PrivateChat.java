/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package businessLogic.Entities;

import java.util.UUID;

/**
 *
 * @author Илья
 */
public class PrivateChat extends Chat {
    public PrivateChat( String name, UUID inputOwner ) {
        super(name);
        ownerID = inputOwner;
    }
    
    public UUID getOwnerID() {
        return ownerID;
    }
    
    protected UUID ownerID;
}
