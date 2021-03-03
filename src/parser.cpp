#include "include/parer.hpp"

void expression::splice_parameter_list_with(expression &&other)
{
    m_parameters.splice(m_parameters.end(), std::move(other.m_parameters));
}
