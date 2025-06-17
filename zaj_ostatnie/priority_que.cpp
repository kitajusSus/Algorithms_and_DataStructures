double sum(std::vector<double>& v){
    double sum=0.0;
    sort(v.begin(), v.end());
    std::vector<double>::const_iterator it;
    it=find_if(v.begin(), v.end(), IsBTZ);
    std::priority_queue<double, std::vector<double>, std::greater<double> > pqp;
    std::priority_queue<double, std::vector<double>, std::less<double> > pqm;
    for(std::vector<double>::const_iterator i=it; i!=v.end(); i++){
        pqp.push(*i);
    //std::cout<<pqp.top() <<"====\n";
    }
    for(std::vector<double>::const_iterator i=v.begin(); i!=it; i++){
        pqm.push(*i);
 //std::cout<<pqm.top() <<"\n";
    }
    while(pqp.size() > 1){
        double x = pqp.top(); pqp.pop();
        double y = pqp.top(); pqp.pop();
        //std::cout<<"["<<x<<"]["<<y<<"]plus\n";
        pqp.push(x+y);
    }
    while(pqm.size() > 1){
        double x = pqm.top(); pqm.pop();
        double y = pqm.top(); pqm.pop();
        //std::cout<<"["<<x<<"]["<<y<<"]mines\n";
        pqm.push(x+y);
    }
    if(pqp.size() == 1)
    sum+=pqp.top();
    if(pqm.size() == 1)
    sum+=pqm.top();
    return sum;
}
