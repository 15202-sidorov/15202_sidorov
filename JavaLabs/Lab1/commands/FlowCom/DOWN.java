package Lab1.commands.FlowCom

import FlowCommand

public class DOWN extends FlowCommand {
	public DOWN(Flow f) {
		super(f);
	}

	public void execute() {
		flow.pointer.down();
	}

	private DOWN() {}
}