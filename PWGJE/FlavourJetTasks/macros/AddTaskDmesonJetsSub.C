/// \file AddTaskDmesonJets.C
/// \brief AddTask macro for the AliAnalysisTaskDmesonJets class.
///
/// AddTask macro for the AliAnalysisTaskDmesonJets class.
///
/// \author Salvatore Aiola <salvatore.aiola@cern.ch>, Yale University
/// \date Feb 12, 2016

AliAnalysisTaskDmesonJetsSub* AddTaskDmesonJetsSub(
    const char *ntracks    = "usedefault",
    const char *nclusters  = "usedefault",
    const char *nMCpart    = "",
    Int_t       nMaxTrees  = 2,
    const char *suffix     = ""
)
{  
 return AliAnalysisTaskDmesonJetsSub::AddTaskDmesonJetsSub(ntracks, nclusters, nMCpart, nMaxTrees, suffix);
}
