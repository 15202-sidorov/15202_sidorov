package Lab1.commands.FlowCom;

import Lab1.commands.Command; 
import Lab1.flow.Flow;

public abstract class FlowCommand implements Command {
	public FlowCommand(Flow f) {
		flow = f;
	}
	
	public void execute();

	private FlowCommand() {}
	private Flow flow;
}