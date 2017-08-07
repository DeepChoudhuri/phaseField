// =================================================================================
// NUCLEATION FUNCTIONS
// =================================================================================

// =================================================================================
// Nucleation probability
// =================================================================================
// template <int dim, int degree>
// double customPDE<dim,degree>::nucProb(double cValue, double dV) const
// {
// 	// Calculate the nucleation rate
// 	double J=k1*exp(-k2/(std::max(cValue,1.0e-6)) - tau/(this->currentTime));
// 	double retProb=1.0-exp(-J*timeStep*((double)skipNucleationSteps)*dV);
//     return retProb;
// }

template <int dim, int degree>
double customPDE<dim,degree>::getNucleationProbability(variableValueContainer variable_value, double dV, dealii::Point<dim> p) const
{
	//Supersaturation factor
    double ssf;
	double calmin = 0.00052;
    if (dim ==2) ssf=variable_value(0)-calmin;
    if (dim ==3) ssf=(variable_value(0)-calmin)*(variable_value(0)-calmin);
	// Calculate the nucleation rate
	double J=k1*exp(-k2/(std::max(ssf,1.0e-6)))*exp(-tau/(this->currentTime));
	double retProb=1.0-exp(-J*userInputs.dtValue*((double)userInputs.steps_between_nucleation_attempts)*dV);
    return retProb;
}