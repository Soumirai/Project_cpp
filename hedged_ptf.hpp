#ifndef HEDGED_PTF_HPP
#define HEDGED_PTF_HPP

// libs of the project

#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

namespace project
{
	
	namespace BS
	{

		
		/* -------------------------------- */
		/* ---- DELTA-HEDGED PORTFOLIO ---- */
		/* -------------------------------- */
		
		// class of the delta-hedged portfolio we will manipulate
		class hedged_ptf
		{
		public:
			
			// constructors
			hedged_ptf(const std::string& name, std::ifstream& csv_file,
					   double strike = 100.0, double rate = 0.01, double div = 0.0);
			
			// destructor
			~hedged_ptf();
			
			// access - general
			std::string get_name() const;
			std::size_t get_size() const;
			std::size_t get_size_range() const; // between start and end

			
			// access - values
			double get_spot() const;
			double get_maturity() const;
			double get_strike() const;
			double get_rate() const;
			double get_div() const;
			
			// access - time_series
			const TS::time_series& get_ts() const;
			
			// access - date range
			std::size_t get_start() const;
			std::size_t get_end() const;
			
			
			// printing
			void print_info() const;
			// void print_range() const;
			
			
			
			// modify - general
			void let_name(std::string name);
			
			// modify - values
			void let_strike(double strike, bool percent = true);
			void let_rate(double rate);
			void let_div(double div);
			
			// modify - date range
			void let_start(std::size_t start);
			void let_end(std::size_t end);
			void let_range(std::size_t start, std::size_t end);
			
			
			// sets range to last n months (for vol computations)
			void let_last_range(std::size_t n, bool next = true); // uses shift_months
			
			
			// P&L computations
			double get_pnl(double vol, bool call = true) const; // auto-financing portfolio
			double get_delta_pnl(double vol, bool call = true) const; // only delta effect
			double get_robust_pnl(double vol, bool call = true) const; // gamma weighted average method
			
			// implied vol computations
			double get_implied_vol(bool robust_pnl = false, double tol = 1e-13, double precision = 1e-5, double v_low = 0.0, double v_high = 1.0) const;
			double get_implied_vol_old(double precision = 1e-5, double v_low = 0.0, double v_high = 1.0) const;
			
			
			
			
		private:
			
			// data members
			
			// parameters
			double m_strike;
			double m_rate;
			double m_div;
			
			// time_series
			TS::time_series m_ts;
			std::size_t m_start;
			std::size_t m_end;
			
			
		};

	}

}



#endif