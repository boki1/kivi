```cpp

compiler
{
	emitter { }

	register_allocation
	{
		vregister_descriptor { vreg, data:=vector<vreg> }

		register_descriptor { machine_target_ns::native_register, data:=vector<vreg> }

		basic_block { begin: const_iterator, end: const_iterator, id = 0++ }
		
		liveness_analyzer {
			block:=basic_block{}, table:=std::map<vreg, entry>
		
			analyze(basic_block block) {
				
			}
		}
	}
	
	/* instruction_selection.hh|.cc */
	instruction_selection
	{
		map(ir::TAC, const machine_target &target) -> native_instruction {
			target.map()	
		}
	}
	
	/* arch/all.hh */
	machine_target_ns
	{
		class native_instruction { ... }

		class machine_target {
			map(ir::TAC) -> native_instruction			
		}
		
		class native_register { }	
	}
	
	/* arch/x86_64.hh|cc */
	namespace machine_target_ns
	{			
	namespace x86_64_ns
	{
		class x86_64 : machine_target
		{
			std::map<> registers = ... ;	
			map(ir::TAC) -> x86_64 instruction { ... }
		};

		class x86_64_instruction : native_instruction { };
	}

}

```