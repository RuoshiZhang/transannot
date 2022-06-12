#ifndef LOCALPARAMETERS_H
#define LOCALPARAMETERS_H

#include <Parameters.h>

class LocalParameters : public  Parameters {
public:
    static void initInstance() {
        new LocalParameters;
    }

    static LocalParameters& getLocalInstance() {
        if (instance == nullptr) {
            initInstance();
        }
        return static_cast<LocalParameters&>(LocalParameters::getInstance());
    }

    std::vector<MMseqsParameter*> assemble;
    std::vector<MMseqsParameter*> annotateworkflow;
    std::vector<MMseqsParameter*> downloaddb;
    std::vector<MMseqsParameter*> contaminationworkflow;
    std::vector<MMseqsParameter*> createdbworkflow;
    std::vector<MMseqsParameter*> annotateprofiles;

    PARAMETER(PARAM_INFORMATION_SELECTION)


    std::vector<MMseqsParameter*> combineList(const std::vector<MMseqsParameter*> &par1,
                                            const std::vector<MMseqsParameter*> &par2);

    int infoSelect;
    int taxId;

private:
    LocalParameters() :
        Parameters(),
        PARAM_INFORMATION_SELECTION(PARAM_INFORMATION_SELECTION_ID, "--information-selection", "Information about sequence", "What information about the input sequence should be provided, KEGG: 0, ExPASy: 1, Pfam: 2, eggNOG: 3, SCOP: 4, AlphaFold: 5, all: 6 ", typeid(int), (void *) &infoSelect, "^[0-6]{1}$"),
        PARAM_TAXONOMYID(PARAM_TAXONOMYID_ID, "--taxid", "Taxonomy ID", "Taxonomy ID to run search against proteins from particular organism. 10-digits unique number", typeid(int), (void *) &taxId, "^[0-9]{7}$"),

    {
        assemble.push_back(&PARAM_COMPRESSED);
        assemble.push_back(&PARAM_THREADS);
        assemble.push_back(&PARAM_V);

        annotateworkflow.push_back(&PARAM_HELP);
        annotateworkflow.push_back(&PARAM_HELP_LONG);
        annotateworkflow.push_back(&PARAM_INFORMATION_SELECTION);
        annotateworkflow.push_back(&PARAM_TAXONOMYID);
        annotateworkflow.push_back(&PARAM_COMPRESSED);
        annotateworkflow.push_back(&PARAM_THREADS);
        annotateworkflow.push_back(&PARAM_V);

        annotateprofiles = annotateprofiles; //same parameters so far, later combineList() may be used

        downloaddb.push_back(&PARAM_THREADS);
        downloaddb.push_back(&PARAM_V);

        contaminationworkflow.push_back(&PARAM_COMPRESSED);
        contaminationworkflow.push_back(&PARAM_THREADS);
        contaminationworkflow.push_back(&PARAM_V);

        createdbworkflow.push_back(&PARAM_THREADS);
        createdbworkflow.push_back(&PARAM_V);

        // default values
        infoSelect = 6;
    }
    LocalParameters(LocalParameters const&);
    ~LocalParameters() {};
    void operator=(LocalParameters const&);
};

#endif