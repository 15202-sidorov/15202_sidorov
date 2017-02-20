package Lab1.commands.FlowCom;

import FlowCommand;

public class UP extends FlowCommand {
	public UP(Flow f) {
		super(f);
	}
	
	public void execute() {
		flow.pointer.up();
	}

	private UP() {}
}