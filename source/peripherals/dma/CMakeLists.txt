include(CTEmbedded)

gen_static_lib_variants(
  TARGET
    chimera_sim_dma
  SOURCES
    sim_chimera_dma.cpp
  PRV_LIBRARIES
    aurora_intf_inc
    chimera_intf_inc
    chimera_sim_intf_inc
  EXPORT_DIR
    "${PROJECT_BINARY_DIR}/ChimeraSim/dma"
)
