#ifndef COMMAND_H
#define COMMAND_H

class Command {
	public:
		virtual void execute() const = 0;
};

#endif
