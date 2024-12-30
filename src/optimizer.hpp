#pragma once

#include <utility>
#include "ensmallen.hpp"
#include "typedefs.hpp"
#include "lossfunction.hpp"
#include "callbacks.hpp"


class SPSA{

private:
	ens::SPSA opt_;

public:
	SPSA() = default;

	template<typename LossFunction>
	np_array<double> optimize(const LossFunction * func, const np_array<double> & p0){
		//arma::mat p(p0.data(), p0.shape(0), p0.shape(1));
		arma::mat p = arma::mat(p0.shape(0), p0.shape(1));
		for (unsigned i = 0; i < p0.shape(0); ++i){
			for (unsigned j = 0; j < p0.shape(1); ++j){
				p(i,j) = p0.at(i,j);
			}
		}
		opt_.Optimize(*func, p, ens::Report(0.1), Progress());
		//return np_array<double>({p.n_rows,p.n_cols}, p.memptr());
		np_array<double> result = np_array<double>({p.n_rows,p.n_cols});
		for (unsigned i = 0; i < p.n_rows; ++i){
			for (unsigned j = 0; j < p.n_cols; ++j){
				result.mutable_at(i,j) = p(i,j);
			}
		}
		return result;
	}

	void alpha(double alpha){
		opt_.Alpha() = alpha;
	}
	double alpha() const{
		return opt_.Alpha();
	}

	void gamma(double gamma){
		opt_.Gamma() = gamma;
	}
	double gamma() const{
		return opt_.Gamma();
	}

	void stepSize(double stepSize){
		opt_.StepSize() = stepSize;
	}
	double stepSize() const{
		return opt_.StepSize();
	}

	void evaluationStepSize(double evaluationStepSize){
		opt_.EvaluationStepSize() = evaluationStepSize;
	}
	double evaluationStepSize() const{
		return opt_.EvaluationStepSize();
	}

	void maxIterations(size_t maxIterations){
		opt_.MaxIterations() = maxIterations;
	}
	size_t maxIterations() const{
		return opt_.MaxIterations();
	}

	void tolerance(double tolerance){
		opt_.Tolerance() = tolerance;
	}
	double tolerance() const{
		return opt_.Tolerance();
	}

};



class SA{

private:
	ens::SA<> opt_;

public:
	SA() = default;

	template<typename LossFunction>
	np_array<double> optimize(const LossFunction * func, const np_array<double> & p0){
		//arma::mat p(p0.data(), p0.shape(0), p0.shape(1));
		arma::mat p = arma::mat(p0.shape(0), p0.shape(1));
		for (unsigned i = 0; i < p0.shape(0); ++i){
			for (unsigned j = 0; j < p0.shape(1); ++j){
				p(i,j) = p0.at(i,j);
			}
		}
		opt_.Optimize(*func, p, ens::Report(0.1), Progress());
		//return np_array<double>({p.n_rows,p.n_cols}, p.memptr());
		np_array<double> result = np_array<double>({p.n_rows,p.n_cols});
		for (unsigned i = 0; i < p.n_rows; ++i){
			for (unsigned j = 0; j < p.n_cols; ++j){
				result.mutable_at(i,j) = p(i,j);
			}
		}
		return result;
	}

	void maxIterations(unsigned max_iters){
		opt_.MaxIterations() = max_iters;
	}
	unsigned maxIterations() const{
		return opt_.MaxIterations();
	}

	void temperature(double temp){
		opt_.Temperature() = temp;
	}
	double temperature() const{
		return opt_.Temperature();
	}

	void initialMoves(unsigned initial_moves){
		opt_.InitMoves() = initial_moves;
	}
	unsigned initialMoves() const{
		return opt_.InitMoves();
	}

	void moveCtrlSweep(unsigned move_ctrl_sweep){
		opt_.MoveCtrlSweep() = move_ctrl_sweep;
	}
	unsigned moveCtrlSweep() const{
		return opt_.MoveCtrlSweep();
	}
	
	void tolerance(double tolerance){
		opt_.Tolerance() = tolerance;
	}
	double tolerance() const{
		return opt_.Tolerance();
	}

	void maxToleranceSweep(unsigned max_tolerance_sweep){
		opt_.MaxToleranceSweep() = max_tolerance_sweep;
	}
	unsigned maxToleranceSweep() const{
		return opt_.MaxToleranceSweep();
	}

	void maxMoveCoef(double max_move_coef){
		opt_.MaxMoveCoef() = max_move_coef;
	}
	double maxMoveCoef() const{
		return opt_.MaxMoveCoef();
	}

	void initMoveCoef(double init_move_coef){
		opt_.InitMoveCoef() = init_move_coef;
	}
	double initMoveCoef() const{
		return opt_.InitMoveCoef();
	}

	void gain(double gain){
		opt_.Gain() = gain;
	}
	double gain() const{
		return opt_.Gain();
	}
	
};