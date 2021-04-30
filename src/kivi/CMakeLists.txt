add_executable(
	kivi
	main.cc
	parser.cc
	parser.hh
	)

target_link_libraries(kivi PRIVATE kivi_parser)
