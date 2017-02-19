package Lab1.commands.FlowCom

import FlowCommand

public class RIGHT extends FlowCommand {
	public RIGHT(Flow f) {
		super(f);
	}

	public void execute() {
		flow.pointer.right();
	}

	private RIGHT() {}
}