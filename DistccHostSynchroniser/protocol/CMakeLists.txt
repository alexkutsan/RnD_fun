add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/rpc_protocol_generated.h
    COMMAND ${FLATC} --cpp "${CMAKE_CURRENT_SOURCE_DIR}/rpc_protocol.fbs"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/rpc_protocol.fbs")

add_custom_target(generate_protocol DEPENDS
    "${CMAKE_CURRENT_BINARY_DIR}/rpc_protocol_generated.h")
