package Lab1.commands.FlowCom;

import Lab1.commands.FlowCom.FlowCommand;

public class UP extends FlowCommand {
	public UP(Flow f) {
		super(f);
	}
	
	public void execute() {
		flow.pointer.up();
	}

	private UP() {}
}