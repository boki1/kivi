#ifndef KIVI_LIVELINESS_ANALYZER_HH
#define KIVI_LIVELINESS_ANALYZER_HH

namespace compiler
{
    class liveness_analyzer
    {
    public:
        class rule
        {
        private:
            std::vector<bool> m_predicates;
//            std::vector<...> m_preposition;
        public:
            void evaluate();
        };

    private:
        std::vector<rule> m_rules;
    public:
        void add_element();
        void build();
    };
}

#endif //KIVI_LIVELINESS_ANALYZER_HH
