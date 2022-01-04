add_library(treelist_lib TLNode.h TreeListIterator.h TreeList.h)
set_target_properties(treelist_lib PROPERTIES LINKER_LANGUAGE CXX)
install(FILES TLNode.h TreeListIterator.h TreeList.h DESTINATION include)
