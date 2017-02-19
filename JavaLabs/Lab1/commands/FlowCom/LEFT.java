package Lab1.commands.FlowCom

import FlowCommand

public class LEFT extends FlowCommand {
	public LEFT(Flow f) {
		super(f);
	}

	public void execute() {
		flow.pointer.left();
	}

	private LEFT() {}
}